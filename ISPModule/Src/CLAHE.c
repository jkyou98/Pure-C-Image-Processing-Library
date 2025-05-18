/**
 * @file CLAHE.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of CLAHE.
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "CLAHE.h"
#include "MakeBorder.h"
#include "param.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *
CLAHE_error_str (CLAHE_error_t err)
{
  const char *err_str = NULL;
  const char *const CLAHE_ERROR_STRS[] = {
    "CLAHE_ERROR_OK",
    "CLAHE_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= CLAHE_ERROR_COUNT)
    {
      goto done;
    }

  err_str = CLAHE_ERROR_STRS[err];

done:
  return err_str;
}

static void
ClipHist (uint32_t *Hist, uint16_t bins, uint32_t p_num_t)
{
  uint32_t bin_inc, Upper;
  int32_t Total_excess = 0, P_excess;
  // count the total excess pixels
  for (uint16_t i = 0; i < bins; ++i)
    {
      P_excess = Hist[i] - p_num_t;
      if (P_excess > 0)
        Total_excess += P_excess;
    }
  // avg. excess pixel to spread
  bin_inc = (uint32_t)(Total_excess / bins);
  Upper = p_num_t - bin_inc;

  for (uint16_t i = 0; i < bins; i++)
    {
      if (Hist[i] > p_num_t)
        Hist[i] = p_num_t;
      else
        {
          if (Hist[i] > Upper)
            {
              Total_excess -= Hist[i] - Upper;
              Hist[i] = p_num_t;
            }
          else
            {
              Total_excess -= bin_inc;
              Hist[i] += bin_inc;
            }
        }
    }
  uint32_t *Bin = Hist;
  uint32_t *End;
  uint32_t *Start = Hist;
  uint32_t step;
  // if excess pixels are left, spread to bins with step
  while (Total_excess)
    {
      End = &Hist[bins];
      while (Total_excess && Start < End)
        {
          step = (uint32_t)(bins / Total_excess);
          if (step < 1)
            step = 1;

          for (Bin = Start; Bin < End && Total_excess; Bin += step)
            {
              if (*Bin < p_num_t)
                {
                  (*Bin)++;
                  Total_excess--;
                }
            }
          Start++;
        }
    }
}

static void
CalHist (uint8_t *block_image, uint16_t im_w, uint16_t b_w, uint16_t b_h,
         uint32_t *Hist)
{
  // hist count of each block
  for (uint16_t i = 0; i < b_h; ++i)
    {
      for (uint16_t j = 0; j < b_w; ++j)
        {
          Hist[block_image[i * im_w + j]]++;
        }
    }
}

static void
MapHist (uint32_t *Hist, uint16_t bins, uint8_t p_min, uint8_t p_max)
{
  //// cdf function of each block////
  // turn histogram to cdf
  for (uint16_t bin_cdf_ix = 1; bin_cdf_ix < bins; ++bin_cdf_ix)
    {
      Hist[bin_cdf_ix] = Hist[bin_cdf_ix] + Hist[bin_cdf_ix - 1];
    }
  // find the minimum non-zero bin
  uint8_t k = 0;
  while (!Hist[k])
    ++k;

  uint8_t temp;

  for (uint16_t bin = 0; bin < bins; ++bin)
    {
      // check cdf mapping
      for (uint16_t bin_ix = 0; bin_ix < bins; ++bin_ix)
        {
          if (bin < (bin_ix + 1) + p_min && bin >= bin_ix + p_min)
            {
              temp = (uint8_t)bin_ix;
            }
        }

      // cdf function
      Hist[bin] = (uint8_t)((float)(Hist[temp] - Hist[k]) * (p_max - p_min)
                                / (Hist[bins - 1] - Hist[k])
                            + p_min);
      if (Hist[bin] < p_min)
        Hist[bin] = p_min;
      if (Hist[bin] > p_max)
        Hist[bin] = p_max;
    }
}

static void
Interpolate (uint8_t *image, uint16_t width, uint8_t b_h, uint8_t b_w,
             uint32_t *LUT_LU, uint32_t *LUT_RU, uint32_t *LUT_LB,
             uint32_t *LUT_RB)
{
  // interpolation
  int16_t x_d, x_d_inv, y_d, y_d_inv, i_size;
  i_size = (uint16_t)b_h * b_w;
  for (y_d = 0, y_d_inv = (int16_t)b_h; y_d < (int16_t)b_h; ++y_d, --y_d_inv)
    {
      for (x_d = 0, x_d_inv = (int16_t)b_w; x_d < (int16_t)b_w;
           ++x_d, --x_d_inv)
        {
          image[y_d * width + x_d]
              = (uint8_t)((y_d_inv
                               * (x_d_inv * LUT_LU[image[y_d * width + x_d]]
                                  + x_d * LUT_RU[image[y_d * width + x_d]])
                           + y_d
                                 * (x_d_inv * LUT_LB[image[y_d * width + x_d]]
                                    + x_d * LUT_RB[image[y_d * width + x_d]]))
                          / i_size);
        }
    }
}

static void
CLAHE_uint8_t (uint8_t *image, uint8_t *image_padding, uint32_t *CDF_map,
               uint8_t width, uint16_t height, uint16_t b_width,
               uint16_t b_height, uint8_t grid_x, uint8_t grid_y,
               uint16_t image_padding_w, uint16_t image_padding_h,
               uint16_t padding_w, uint16_t padding_h, float S_limit)
{
  uint16_t bins = 256;
  uint8_t p_min = 0, p_max = 255;
  uint32_t p_num_t;
  uint32_t *Hist = NULL;

  uint8_t *block = NULL;
  uint32_t *LUT_LU, *LUT_RU, *LUT_LB, *LUT_RB;
  uint8_t *image_pointer = NULL;

  // generate border reflect for CLAHE
  MakeBorder (image, image_padding, width, height, 0, padding_h, 0, padding_w);

  // set bin threshold
  if (S_limit > 0.0)
    {
      p_num_t = (uint32_t)(S_limit * (b_width * b_height) / bins);
      p_num_t = (p_num_t < 1) ? 1 : p_num_t;
    }

  // set mappinng table
  for (uint8_t i = 0; i < grid_y; ++i)
    {
      for (uint8_t j = 0; j < grid_x; ++j)
        {
          block = &image_padding[(i * b_height) * image_padding_w
                                 + (j * b_width)];
          Hist = &CDF_map[(i * grid_x + j) * bins];
          CalHist (block, image_padding_w, b_width, b_height, Hist);
          ClipHist (Hist, bins, p_num_t);
          MapHist (Hist, bins, p_min, p_max);
        }
    }
  // interpolation & cdf mapping
  uint16_t sub_x, sub_y, UY, BY, LX, RX;
  image_pointer = image_padding;
  for (uint8_t i = 0; i <= grid_y; ++i)
    {
      if (i == 0)
        { /* special case: top row */
          sub_y = b_height / 2;
          UY = 0;
          BY = 0;
        }
      else
        {
          if (i == grid_y)
            { /* special case: bottom row */
              sub_y = (b_height + 1) / 2;
              UY = grid_y - 1;
              BY = UY;
            }
          else
            { /* default values */
              sub_y = b_height;
              UY = i - 1;
              BY = UY + 1;
            }
        }

      for (uint8_t j = 0; j <= grid_x; ++j)
        {
          if (j == 0)
            { /* special case: left column */
              sub_x = b_width / 2;
              LX = 0;
              RX = 0;
            }
          else
            {
              if (j == grid_x)
                { /* special case: right column */
                  sub_x = (b_width + 1) / 2;
                  LX = grid_x - 1;
                  RX = LX;
                }
              else
                { /* default values */
                  sub_x = b_width;
                  LX = j - 1;
                  RX = LX + 1;
                }
            }

          LUT_LU = &CDF_map[bins * (UY * grid_x + LX)];
          LUT_RU = &CDF_map[bins * (UY * grid_x + RX)];
          LUT_LB = &CDF_map[bins * (BY * grid_x + LX)];
          LUT_RB = &CDF_map[bins * (BY * grid_x + RX)];
          Interpolate (image_pointer, image_padding_w, sub_y, sub_x, LUT_LU,
                       LUT_RU, LUT_LB, LUT_RB);
          image_pointer += sub_x;
        }
      image_pointer += (sub_y - 1) * image_padding_w;
    }

  // update image buffer
  for (uint16_t i = 0; i < height; ++i)
    {
      for (uint16_t j = 0; j < width; ++j)
        {
          image[i * width + j] = image_padding[i * image_padding_w + j];
        }
    }
}

CLAHE_error_t
CLAHE (ImageInfo *IMG, CLAHE_param *PARAM)
{
  // pointer check
  if (IMG->image == NULL || IMG->image == NULL)
    return CLAHE_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      CLAHE_uint8_t ((uint8_t *)IMG->image, (uint8_t *)PARAM->image_padding,
                     (uint32_t *)PARAM->CDF_map, IMG->width, IMG->height,
                     PARAM->b_width, PARAM->b_height, PARAM->grid_x,
                     PARAM->grid_y, PARAM->image_padding_w,
                     PARAM->image_padding_h, PARAM->padding_w,
                     PARAM->padding_h, PARAM->S_limit);
      IMG->update_status = 2;
    }
  return CLAHE_ERROR_OK;
}