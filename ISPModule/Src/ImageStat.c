/**
 * @file ImageStat.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of ImageStat
 * @version 0.1
 * @date 2022-01-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "ImageStat.h"
#include "MinMax_Arr.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *
ImageStat_error_str (ImageStat_error_t err)
{
  const char *err_str = NULL;
  const char *const IMAGESTAT_ERROR_STRS[] = {
    "IMAGESTAT_ERROR_OK",
    "IMAGESTAT_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= IMAGESTAT_ERROR_COUNT)
    {
      goto done;
    }

  err_str = IMAGESTAT_ERROR_STRS[err];

done:
  return err_str;
}

ImageStat_error_t
ImageStat (uint8_t *image, uint16_t height, uint16_t width, float *Mean,
           float *Std, float *sigma_min, float *sigma_max, float *sigma_total,
           uint8_t *Min, uint8_t *Max)
{
  // pointer check
  if (image == NULL || Mean == NULL || Std == NULL || sigma_min == NULL
      || sigma_max == NULL || sigma_total == NULL || Min == NULL
      || Max == NULL)
    return IMAGESTAT_ERROR_INVARG;

  uint32_t total, total_std;
  uint8_t min, max;
  float z_max, z_min, mean, mean_std, std;
  max = FindMaxEle_uint8_t (image, height * width);
  min = FindMinEle_uint8_t (image, height * width);

  total = 0;
  total_std = 0;
  for (uint16_t i = 0; i < height; ++i)
    {
      for (uint16_t j = 0; j < width; ++j)
        {
          total += image[width * i + j];
          total_std += (image[width * i + j] * image[width * i + j]);
        }
    }
  mean = (float)total / (height * width);
  mean_std = (float)total_std / (height * width);

  std = sqrtf (mean_std - mean * mean);
  z_max = (max - mean) / std;
  z_min = (mean - min) / std;

  *sigma_min = z_min;
  *sigma_max = z_max;
  *sigma_total = z_min + z_max;
  *Min = min;
  *Max = max;
  *Mean = mean;
  *Std = std;
  return IMAGESTAT_ERROR_OK;
}