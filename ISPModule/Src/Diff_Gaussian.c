/**
 * @file Diff_Gaussian.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Diff_Gaussian.h"
#include "MinMax_Mapping.h"
#include "gaussian_blur.h"
#include "param.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *
Diff_Gaussian_error_str (Diff_Gaussian_error_t err)
{
  const char *err_str = NULL;
  const char *const DIFF_GAUSSIAN_ERROR_STRS[] = {
    "DIFF_GAUSSIAN_ERROR_OK",
    "DIFF_GAUSSIAN_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= DIFF_GAUSSIAN_ERROR_COUNT)
    {
      goto done;
    }

  err_str = DIFF_GAUSSIAN_ERROR_STRS[err];

done:
  return err_str;
}

static void
Diff_Gaussian_uint8_t (uint8_t *image, uint8_t *image_padding,
                       uint8_t *image_blur_1, uint8_t *image_blur_2,
                       float *Gauss_filter, int16_t *DOG_raw, uint16_t width,
                       uint16_t height, uint8_t radius_1, uint8_t radius_2)
{

  // Gaussain blur with different radius
  gaussian_blur (image, image_padding, Gauss_filter, image_blur_1, height,
                 width, radius_1);
  gaussian_blur (image, image_padding, Gauss_filter, image_blur_2, height,
                 width, radius_2);
  // Difference of Gausssain
  for (uint32_t i = 0; i < (uint32_t)height * width; i++)
    {
      DOG_raw[i] = (int16_t)(image_blur_1[i] - image_blur_2[i]);
    }
  // Normalizing to [0,255]
  MinMax_int16_t (DOG_raw, image, height, width);
}

Diff_Gaussian_error_t
Diff_Gaussian (ImageInfo *IMG, Diff_Gaussian_param *PARAM)
{
  // pointer check
  if (IMG->image == NULL || IMG->image == NULL)
    return DIFF_GAUSSIAN_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      Diff_Gaussian_uint8_t (
          (uint8_t *)IMG->image, (uint8_t *)PARAM->image_padding,
          (uint8_t *)PARAM->image_blur1, (uint8_t *)PARAM->image_blur2,
          (float *)PARAM->Gauss_filter, (int16_t *)PARAM->DOG_raw, IMG->width,
          IMG->height, PARAM->radius1, PARAM->radius2);
      IMG->update_status = 1;
    }
  return DIFF_GAUSSIAN_ERROR_OK;
}