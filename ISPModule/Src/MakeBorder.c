/**
 * @file MakeBorder.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of MakeBorder.
 * @version 0.1
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "MakeBorder.h"
#include <stdio.h>

const char *
MakeBorder_error_str (MakeBorder_error_t err)
{
  const char *err_str = NULL;
  const char *const MAKEBORDER_ERROR_STRS[] = {
    "MAKEBORDER_ERROR_OK",
    "MAKEBORDER_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= MAKEBORDER_ERROR_COUNT)
    {
      goto done;
    }

  err_str = MAKEBORDER_ERROR_STRS[err];

done:
  return err_str;
}

MakeBorder_error_t
MakeBorder (uint8_t *image, uint8_t *image_padding, uint16_t width,
            uint16_t height, uint8_t top, uint8_t bottom, uint8_t left,
            uint8_t right)
{
  // pointer check
  if (image == NULL || image_padding == NULL)
    return MAKEBORDER_ERROR_INVARG;

  uint16_t w_new = left + right + width, h_new = top + bottom + height;
  uint16_t i, j;
  for (i = top; i < height + top; ++i)
    {
      for (j = left; j < width + left; ++j)
        {
          image_padding[i * w_new + j] = image[(i - top) * width + (j - left)];
        }
    }

  // Border_Reflect
  // top reflect
  for (i = 1; i < top + 1; ++i)
    {
      for (j = left; j < width + left; ++j)
        {

          image_padding[(top - i) * w_new + j]
              = image_padding[(top + i) * w_new + j];
        }
    }
  // bottom reflect
  for (i = 1; i < bottom + 1; ++i)
    {
      for (j = left; j < width + left; ++j)
        {
          image_padding[(top + (height - 1) + i) * w_new + j]
              = image_padding[(top + (height - 1) - i) * w_new + j];
        }
    }
  // left reflect
  for (i = 0; i < h_new; ++i)
    {
      for (j = 1; j < left + 1; ++j)
        {
          image_padding[i * w_new + (left - j)]
              = image_padding[i * w_new + (left + j)];
        }
    }
  // right reflect
  for (i = 0; i < h_new; ++i)
    {
      for (j = 1; j < right + 1; ++j)
        {
          image_padding[i * w_new + (left + (width - 1) + j)]
              = image_padding[i * w_new + (left + (width - 1) - j)];
        }
    }
  return MAKEBORDER_ERROR_OK;
}