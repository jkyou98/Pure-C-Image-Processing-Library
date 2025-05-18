/**
 * @file Mean_Filter.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of Mean_Filter
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Mean_Filter.h"
#include "Border_Reflect.h"
#include "param.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *
Mean_Filter_error_str (Mean_Filter_error_t err)
{
  const char *err_str = NULL;
  const char *const MEAN_FILTER_ERROR_STRS[] = {
    "MEAN_FILTER_ERROR_OK",
    "MEAN_FILTER_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= MEAN_FILTER_ERROR_COUNT)
    {
      goto done;
    }

  err_str = MEAN_FILTER_ERROR_STRS[err];

done:
  return err_str;
}

static void
Mean (uint8_t *proc_arr, uint8_t *result, uint16_t height, uint16_t width,
      uint8_t mask_size)
{
  uint16_t acc, w, i, j, g_i, g_j, proc_size, Padding = mask_size / 2;
  proc_size = width + Padding * 2;
  // Mean Filter with masksize = 3
  if (mask_size == 3)
    {
      for (i = Padding; i < height + Padding; ++i)
        {
          for (j = Padding; j < width + Padding; ++j)
            {
              acc = 0;
              for (g_i = 0; g_i < mask_size; ++g_i)
                {
                  for (g_j = 0; g_j < mask_size; ++g_j)
                    {
                      acc += proc_arr[((i - Padding) + g_i) * proc_size
                                      + ((j - Padding) + g_j)];
                    }
                }
              proc_arr[i * proc_size + j] = (uint8_t)(acc / 9);
              result[(i - Padding) * width + (j - Padding)]
                  = proc_arr[i * proc_size + j];
            }
        }
    }
  // Mean Filter with masksize = 5
  if (mask_size == 5)
    {
      for (i = Padding; i < height + Padding; ++i)
        {
          for (j = Padding; j < width + Padding; ++j)
            {
              acc = 0;
              w = 0;
              for (g_i = 0; g_i < mask_size; ++g_i)
                {
                  for (g_j = 0; g_j < mask_size; ++g_j)
                    {
                      if (g_i == Padding && g_j == Padding)
                        {
                          acc += (3
                                  * proc_arr[((i - Padding) + g_i) * proc_size
                                             + ((j - Padding) + g_j)]);
                          w += 3;
                          continue;
                        }
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
                              acc += proc_arr[((i - Padding) + g_i) * proc_size
                                              + ((j - Padding) + g_j)];
                              w++;
                            }
                          else
                            {
                              acc += (2
                                      * proc_arr[((i - Padding) + g_i)
                                                     * proc_size
                                                 + ((j - Padding) + g_j)]);
                              w += 2;
                            }
                        }
                    }
                }
              proc_arr[i * proc_size + j] = (uint8_t)(acc / w);

              result[(i - Padding) * width + (j - Padding)]
                  = proc_arr[i * proc_size + j];
            }
        }
    }
}

static void
Mean_Filter_uint8_t (uint8_t *image, uint8_t *image_padding, uint16_t width,
                     uint16_t height, uint8_t MF_size)
{

  // Padding with Border Reflect
  Border_Reflect (image_padding, image, height, width, MF_size);
  // Mean Filter Computation
  Mean (image_padding, image, height, width, MF_size);
}

Mean_Filter_error_t
Mean_Filter (ImageInfo *IMG, Mean_Filter_param *PARAM)
{
  if (IMG->image == NULL || IMG->image == NULL)
    return MEAN_FILTER_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      Mean_Filter_uint8_t ((uint8_t *)IMG->image,
                           (uint8_t *)PARAM->image_padding, IMG->width,
                           IMG->height, PARAM->MF_size);
      IMG->update_status = 2;
    }
  return MEAN_FILTER_ERROR_OK;
}