/**
 * @file Border_Reflect.c\
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of border reflect
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Border_Reflect.h"
#include <stdint.h>
#include <stdio.h>


const char *
Border_Reflect_error_str (Border_Reflect_error_t err)
{
  const char *err_str = NULL;
  const char *const BORDER_REFLECT_ERROR_STRS[] = {
    "BORDER_REFLECT_ERROR_OK",
    "BORDER_REFLECT_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= BORDER_REFLECT_ERROR_COUNT)
    {
      goto done;
    }

  err_str = BORDER_REFLECT_ERROR_STRS[err];

done:
  return err_str;
}

Border_Reflect_error_t
Border_Reflect (uint8_t *proc_arr, uint8_t *image, uint16_t height,
                uint16_t width, uint8_t mask_size)
{
  if (proc_arr == NULL || image == NULL)
    return BORDER_REFLECT_ERROR_INVARG;

  uint16_t i, j, Padding = mask_size / 2, proc_size = width + Padding * 2;

  // Loading Image Data
  for (i = Padding; i < height + Padding; ++i)
    {
      for (j = Padding; j < width + Padding; ++j)
        {
          proc_arr[i * proc_size + j]
              = image[(i - Padding) * width + (j - Padding)];
        }
    }
  // BORDER_REFLECT
  for (i = 1; i < Padding + 1; ++i)
    {
      for (j = Padding; j < width + Padding; ++j)
        {
          proc_arr[(Padding - i) * proc_size + j]
              = proc_arr[(Padding + i) * proc_size + j];
          proc_arr[(Padding + (height - 1) + i) * proc_size + j]
              = proc_arr[(Padding + (height - 1) - i) * proc_size + j];
        }
    }

  for (i = 0; i < height + (mask_size / 2) * 2; ++i)
    {
      for (j = 1; j < Padding + 1; ++j)
        {
          proc_arr[i * proc_size + (Padding - j)]
              = proc_arr[i * proc_size + (Padding + j)];
          proc_arr[i * proc_size + (Padding + (width - 1) + j)]
              = proc_arr[i * proc_size + (Padding + (width - 1) - j)];
        }
    }
  return BORDER_REFLECT_ERROR_OK;
}
