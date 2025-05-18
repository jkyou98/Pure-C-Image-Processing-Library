#include "image_conv.h"
#include <stdint.h>
#include <stdio.h>

void
image_conv_K_f (uint8_t *proc_arr, float *kernel, uint8_t *result,
                uint16_t height, uint16_t width, uint8_t mask_size)
{
  float acc;
  uint16_t i, j, Padding = mask_size / 2, proc_size = width + Padding * 2;
  uint8_t g_i, g_j;

  for (i = Padding; i < height + Padding; ++i)
    {
      for (j = Padding; j < width + Padding; ++j)
        {
          acc = 0.0;
          for (g_i = 0; g_i < mask_size; ++g_i)
            {
              for (g_j = 0; g_j < mask_size; ++g_j)
                {
                  acc += kernel[g_i * mask_size + g_j]
                         * (float)proc_arr[((i - Padding) + g_i) * proc_size
                                           + ((j - Padding) + g_j)];
                }
            }
          result[(i - Padding) * width + (j - Padding)] = (uint8_t)acc;
        }
    }
}

void
image_conv_K_int8_t (uint8_t *proc_arr, int8_t *kernel, int16_t *result,
                     uint16_t height, uint16_t width, uint8_t mask_size)
{
  int16_t acc;
  uint16_t i, j, Padding = mask_size / 2, proc_size = width + Padding * 2;
  uint8_t g_i, g_j;

  for (i = Padding; i < height + Padding; ++i)
    {
      for (j = Padding; j < width + Padding; ++j)
        {
          acc = 0.0;
          for (g_i = 0; g_i < mask_size; ++g_i)
            {
              for (g_j = 0; g_j < mask_size; ++g_j)
                {
                  acc += (int16_t)(kernel[g_i * mask_size + g_j]
                                   * proc_arr[((i - Padding) + g_i) * proc_size
                                              + ((j - Padding) + g_j)]);
                }
            }
          result[(i - Padding) * width + (j - Padding)] = acc;
        }
    }
}
