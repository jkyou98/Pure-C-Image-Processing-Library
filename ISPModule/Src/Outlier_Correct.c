/**
 * @file Outlier_Correct.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of Outlier_Correct
 * @version 0.1
 * @date 2022-01-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Outlier_Correct.h"
#include "Border_Reflect.h"
#include "I_Hist_er.h"
#include "ImageStat.h"
#include "param.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *
Outlier_Correct_error_str (Outlier_Correct_error_t err)
{
  const char *err_str = NULL;
  const char *const OUTLIER_CORRECT_ERROR_STRS[] = {
    "OUTLIER_CORRECT_ERROR_OK",
    "OUTLIER_CORRECT_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= OUTLIER_CORRECT_ERROR_COUNT)
    {
      goto done;
    }

  err_str = OUTLIER_CORRECT_ERROR_STRS[err];

done:
  return err_str;
}

static void
Smoothing (uint8_t *proc_arr, uint8_t *result, uint16_t height, uint16_t width,
           uint8_t max, uint8_t min, uint8_t mask_size)
{
  uint16_t i, j, acc, w, proc_size, Padding = mask_size / 2;
  uint8_t g_i, g_j;

  proc_size = width + Padding * 2;

  if (mask_size == 3)
    {
      for (i = Padding; i < height + Padding; ++i)
        {
          for (j = Padding; j < width + Padding; ++j)
            {
              acc = 0;
              if (proc_arr[i * proc_size + j] > max
                  || proc_arr[i * proc_size + j] < min)
                {
                  for (g_i = 0; g_i < mask_size; ++g_i)
                    {
                      for (g_j = 0; g_j < mask_size; ++g_j)
                        {
                          if (g_i == Padding && g_j == Padding)
                            continue;
                          acc += proc_arr[((i - Padding) + g_i) * proc_size
                                          + ((j - Padding) + g_j)];
                        }
                    }
                  proc_arr[i * proc_size + j]
                      = (uint8_t)(acc / (mask_size * mask_size - 1));
                }

              result[(i - Padding) * width + (j - Padding)]
                  = proc_arr[i * proc_size + j];
            }
        }
    }

  if (mask_size == 5)
    {
      for (i = Padding; i < height + Padding; ++i)
        {
          for (j = Padding; j < width + Padding; ++j)
            {
              acc = 0;
              w = 0;
              if (proc_arr[i * proc_size + j] > max
                  || proc_arr[i * proc_size + j] < min)
                {
                  for (g_i = 0; g_i < mask_size; ++g_i)
                    {
                      for (g_j = 0; g_j < mask_size; ++g_j)
                        {
                          if (g_i == Padding && g_j == Padding)
                            continue;
                          if (g_i == 0 || g_i == 4)
                            {
                              acc += proc_arr[((i - Padding) + g_i) * proc_size
                                              + ((j - Padding) + g_j)];
                              w++;
                            }
                          else
                            {
                              if (g_j == 0 || g_j == 4)
                                {
                                  acc += proc_arr[((i - Padding) + g_i)
                                                      * proc_size
                                                  + ((j - Padding) + g_j)];
                                  w++;
                                }
                              else
                                {
                                  acc += 2
                                         * proc_arr[((i - Padding) + g_i)
                                                        * proc_size
                                                    + ((j - Padding) + g_j)];
                                  w += 2;
                                }
                            }
                        }
                    }
                  proc_arr[i * proc_size + j] = (uint8_t)(acc / w);
                }

              result[(i - Padding) * width + (j - Padding)]
                  = proc_arr[i * proc_size + j];
            }
        }
    }
}

static void
Outlier_Correct_uint8_t (uint8_t *image, uint8_t *image_padding,
                         uint32_t *hist, uint16_t width, uint16_t height,
                         uint8_t SF_size, uint8_t OC_max_iter)
{
  uint8_t min, max, k;
  float Mean, Std, Min_sigma, Max_sigma, Total_sigma;
  k = 0;
  while (k < OC_max_iter)
    {
      // image static
      ImageStat (image, height, width, &Mean, &Std, &Min_sigma, &Max_sigma,
                 &Total_sigma, &min, &max);
      // terminate condition
      if (Total_sigma < 6.0)
        break;
      // initial hist at every iteration
      memset (hist, 0, 256 * sizeof (uint32_t));
      // find 99% pixels for mean pixel value
      I_Hist_er_mean (image, hist, height, width, &min, &max, 0.99);
      // smoothing outliers
      Border_Reflect (image_padding, image, height, width, SF_size);
      Smoothing (image_padding, image, height, width, max, min, SF_size);
      k++;
    }
}

Outlier_Correct_error_t
Outlier_Correct (ImageInfo *IMG, Outlier_Correct_param *PARAM)
{
  // pointer check
  if (IMG->image == NULL || IMG->image == NULL)
    return OUTLIER_CORRECT_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      Outlier_Correct_uint8_t (
          (uint8_t *)IMG->image, (uint8_t *)PARAM->image_padding,
          (uint32_t *)PARAM->hist, IMG->width, IMG->height, PARAM->SF_size,
          PARAM->OC_max_iter);
      IMG->update_status = 1;
    }
  return OUTLIER_CORRECT_ERROR_OK;
}