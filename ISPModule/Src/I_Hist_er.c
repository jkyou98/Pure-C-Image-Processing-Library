/**
 * @file I_Hist_er.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of I_Hist_er
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "I_Hist_er.h"
#include "MinMax_Arr.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *
I_Hist_er_error_str (I_Hist_er_error_t err)
{
  const char *err_str = NULL;
  const char *const I_HIST_ER_ERROR_STRS[]
      = { "I_HIST_ER_ERROR_OK", "I_HIST_ER_ERROR_INVARG",
          "I_HIST_ER_MEAN_ERROR_OK", "I_HIST_ER_MEAN_ERROR_INVARG" };
  // Ensure error codes are within the valid array index range
  if (err >= I_HIST_ER_ERROR_COUNT)
    {
      goto done;
    }

  err_str = I_HIST_ER_ERROR_STRS[err];

done:
  return err_str;
}

I_Hist_er_error_t
I_Hist_er (uint8_t *image, uint16_t height, uint16_t width, uint8_t *lower_B,
           uint8_t *upper_B, float sigma_ratio)
{
  // pointer check
  if (image == NULL || lower_B == NULL || upper_B == NULL)
    return I_HIST_ER_ERROR_INVARG;

  // find the upper/lower bound of the image with sigma ratio (i.e. +- 3 sigma
  // or 2 sigma)
  uint32_t total, total_std;
  uint8_t min, max;
  float z_max, z_min, mean, mean_std, std;
  // find min, max of the image
  max = FindMaxEle_uint8_t (image, height * width);
  min = FindMinEle_uint8_t (image, height * width);
  // calculate the mean and std of image
  total = 0;
  total_std = 0;
  for (int16_t i = 0; i < height; ++i)
    {
      for (int16_t j = 0; j < width; ++j)
        {
          total += image[width * i + j];
          total_std += (image[width * i + j] * image[width * i + j]);
        }
    }
  mean = (float)total / (height * width);
  mean_std = (float)total_std / (height * width);
  std = sqrtf (mean_std - mean * mean);
  // calculate the exact sigma of image
  z_max = ((float)max - mean) / std;
  z_min = (mean - (float)min) / std;
  // calculate the upper/lower bound
  if (sigma_ratio <= z_max) // avoid over [min, max] of the image
    z_max = sigma_ratio;
  if (sigma_ratio <= z_min)
    z_min = sigma_ratio;
  *lower_B = (uint8_t)(mean - z_min * std);
  *upper_B = (uint8_t)(mean + z_max * std);
  return I_HIST_ER_ERROR_OK;
}

I_Hist_er_error_t
I_Hist_er_mean (uint8_t *image, uint32_t *hist, uint16_t height,
                uint16_t width, uint8_t *lower_B, uint8_t *upper_B,
                float f_percent)
{
  // pointer check
  if (image == NULL || hist == NULL || lower_B == NULL || upper_B == NULL)
    return I_HIST_ER_MEAN_ERROR_INVARG;

  // find the upper/lower bound with the percent of image from mean of the
  // image  (i.e. 99%)
  uint16_t pixel_max = 256;
  int16_t lower_cur, upper_cur;
  uint32_t mean, total;

  // image histogram
  for (uint32_t i = 0; i < (uint32_t)width * height; ++i)
    {
      hist[image[i]]++;
    }
  // mean pixel value
  total = 0;
  for (uint32_t i = 0; i < (uint32_t)width * height; ++i)
    {
      total += (uint32_t)image[i];
    }
  mean = total / (uint32_t)(height * width);
  // find the 99% pixels of image from mean value of the image
  uint32_t pixels = hist[mean],
           pixel_max_sel = (uint32_t)(width * height * f_percent);
  uint32_t k = 0, k_up = 0, k_down = 0;
  while (pixels < pixel_max_sel)
    {
      k++;
      // avoid over [0, 255] of the image
      upper_cur = mean + k;
      lower_cur = mean - k;
      if ((upper_cur < pixel_max) && (lower_cur >= 0))
        pixels += hist[upper_cur] + hist[lower_cur], k_up++, k_down++;
      if ((upper_cur < pixel_max) && (lower_cur < 0))
        pixels += hist[upper_cur], k_up++;
      if ((upper_cur >= pixel_max) && (lower_cur >= 0))
        pixels += hist[lower_cur], k_down++;
    }

  *lower_B = mean - k_down;
  *upper_B = mean + k_up;
  return I_HIST_ER_MEAN_ERROR_OK;
}

// void I_Hist_er_cdf(float *image, int height, int width, float *f_min, float
// *f_max, int bins, float f_percent)
// {
// 	int *hist = (int *)calloc(bins, sizeof(int));
// 	float *cdf = (float *)calloc(bins, sizeof(float));
// 	int f_count;
// 	float Min, Max;
// 	Max = FindMaxEle(image, height * width);
// 	Min = FindMinEle(image, height * width);
// 	float bin = 1;
// 	for (int i = 0; i < height; ++i)
// 	{
// 		for (int j = 0; j < width; ++j)
// 		{
// 			for (int bin_ix = 0; bin_ix < bins; ++bin_ix)
// 			{
// 				if (image[i * width + j] < ((bin_ix + 1) * bin)
// &&
// image[i * width + j] >= bin_ix * bin)
// hist[bin_ix]++; 				if (bin_ix == bins - 1
// && image[i * width + j] == ((bin_ix + 1) * bin))
// hist[bin_ix]++;
// 			}
// 		}
// 	}
// 	cdf[0] = hist[0];
// 	for (int bin_ix = 1; bin_ix < bins; ++bin_ix)
// 	{

// 		cdf[bin_ix] = cdf[bin_ix - 1] + hist[bin_ix];
// 	}
// 	f_percent *= (cdf[bins - 1] / 100.0);
// 	f_percent /= 2.0;
// 	int min_ix = 0, max_ix = 0;
// 	while (cdf[min_ix] < f_percent)
// 		min_ix++;
// 	max_ix = bins - 1;
// 	while (cdf[max_ix] >= (cdf[bins - 1] - f_percent))
// 		max_ix--;

// 	*f_min = min_ix * bin + Min;
// 	*f_max = max_ix * bin + Min;
// 	free(hist);
// 	free(cdf);
// }