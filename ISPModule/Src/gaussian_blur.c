/**
 * @file gaussian_blur.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of gaussian blur
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "gaussian_blur.h"
#include "Border_Reflect.h"
#include "image_conv.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *
gaussian_blur_error_str (gaussian_blur_error_t err)
{
  const char *err_str = NULL;
  const char *const GAUSSIAN_BLUR_ERROR_STRS[] = {
    "GAUSSIAN_BLUR_ERROR_OK",
    "GAUSSIAN_BLUR_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= GAUSSIAN_BLUR_ERROR_COUNT)
    {
      goto done;
    }

  err_str = GAUSSIAN_BLUR_ERROR_STRS[err];

done:
  return err_str;
}

static void
gaussian_kernel_f (float *gauss, uint8_t mask_size, float sigma)
{
  float sum = 0.0;
  int K = 1;
  for (uint8_t i = 0; i < mask_size; i++)
    {
      for (uint8_t j = 0; j < mask_size; j++)
        {
          float x = i - (mask_size - 1) / 2.0;
          float y = j - (mask_size - 1) / 2.0;
          gauss[i * mask_size + j] = K
                                     * exp (((powf (x, 2.0) + powf (y, 2.0))
                                             / ((2 * powf (sigma, 2.0))))
                                            * (-1));
          sum += gauss[i * mask_size + j];
        }
    }
  for (uint16_t i = 0; i < mask_size * mask_size; i++)
    {
      gauss[i] /= sum;
    }
}

gaussian_blur_error_t
gaussian_blur (uint8_t *image, uint8_t *image_padding, float *Gauss_kernel,
               uint8_t *image_blur, uint16_t height, uint16_t width,
               uint8_t radius)
{ // pointer check
  if (image == NULL || image_padding == NULL || Gauss_kernel == NULL
      || image_blur == NULL)
    return GAUSSIAN_BLUR_ERROR_INVARG;

  // Gaussain Parameter
  float sigma = (float)radius / 2;
  if (sigma < 1)
    sigma = 1;
  uint8_t mask_size = (2 * radius) + 1;

  // Gaussain Blur
  gaussian_kernel_f (Gauss_kernel, mask_size, sigma);
  Border_Reflect (image_padding, image, height, width, mask_size);
  image_conv_K_f (image_padding, Gauss_kernel, image_blur, height, width,
                  mask_size);
  return GAUSSIAN_BLUR_ERROR_OK;
}
