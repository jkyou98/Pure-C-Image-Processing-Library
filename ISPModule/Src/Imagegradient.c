#include "Border_Reflect.h"
#include "image_conv.h"
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void
matrix_mult (int8_t *arr1, int8_t *arr2, int8_t *result, uint32_t arr1_num,
             uint32_t arr2_num, bool arr1_minus, bool arr2_minus)
{
  uint32_t i, j;
  if (arr1_minus == true && arr2_minus == false)
    {
      for (i = 0; i < arr1_num; ++i)
        {
          for (j = 0; j < arr2_num; ++j)
            {
              result[i * arr2_num + j] = -arr1[i] * arr2[j];
            }
        }
    }
  else if (arr1_minus == false && arr2_minus == true)
    {
      for (i = 0; i < arr1_num; ++i)
        {
          for (j = 0; j < arr2_num; ++j)
            {
              result[i * arr2_num + j] = arr1[i] * -arr2[j];
            }
        }
    }
  else
    {
      for (i = 0; i < arr1_num; ++i)
        {
          for (j = 0; j < arr2_num; ++j)
            {
              result[i * arr2_num + j] = arr1[i] * arr2[j];
            }
        }
    }
}
static void
differential_operator (int8_t *diff, uint16_t degree)
{

  // mask_size = 3
  int8_t *dx = (int8_t *)calloc (3, sizeof (int8_t));
  int8_t *dy = (int8_t *)calloc (3, sizeof (int8_t));

  uint8_t n = (uint8_t)(degree / 45);
  dx[0] = 1;
  dx[1] = 1;
  dx[2] = 1;
  dy[0] = -1;
  dy[1] = 0;
  dy[2] = 1;

  switch (n)
    {
    case 0:
      matrix_mult (dx, dy, diff, 3, 3, false, false);
      break;
    case 1:
      diff[0] = 0, diff[1] = 1, diff[2] = 1;
      diff[3] = -1, diff[4] = 0, diff[5] = 1;
      diff[6] = -1, diff[7] = -1, diff[8] = 0;
      break;
    case 2:
      matrix_mult (dy, dx, diff, 3, 3, true, false);
      break;
    case 3:
      diff[0] = 1, diff[1] = 1, diff[2] = 0;
      diff[3] = 1, diff[4] = 0, diff[5] = -1;
      diff[6] = 0, diff[7] = -1, diff[8] = -1;
      break;
    case 4:
      matrix_mult (dx, dy, diff, 3, 3, false, true);
      break;
    case 5:
      diff[0] = 0, diff[1] = -1, diff[2] = -1;
      diff[3] = 1, diff[4] = 0, diff[5] = -1;
      diff[6] = 1, diff[7] = 1, diff[8] = 0;
      break;
    case 6:
      matrix_mult (dy, dx, diff, 3, 3, false, false);
      break;
    default:
      diff[0] = -1, diff[1] = -1, diff[2] = 0;
      diff[3] = -1, diff[4] = 0, diff[5] = 1;
      diff[6] = 0, diff[7] = 1, diff[8] = 1;
      break;
    }

  free (dx);
  free (dy);
}
/*
static void transpose(int *src, int *dst, const int col, const int row)
{

        for (int n = 0; n < row * col; n++)
        {
                int i = n / row;
                int j = n % row;
                dst[n] = src[row * j + i];
        }
}*/
static void
sobel_operator (int8_t *sobel_x, int8_t *sobel_y, uint8_t mask_size)
{

  int8_t *dx = (int8_t *)calloc (mask_size, sizeof (int8_t));
  int8_t *dy = (int8_t *)calloc (mask_size, sizeof (int8_t));
  uint8_t i, j;
  int8_t *kerI = (int8_t *)calloc (mask_size + 1, sizeof (int8_t));

  for (uint8_t k = 0; k < 2; k++)
    {
      uint8_t order = k;
      uint8_t ksize = mask_size;

      if (ksize == 1)
        kerI[0] = 1;
      else if (ksize == 3)
        {
          if (order == 0)
            kerI[0] = 1, kerI[1] = 2, kerI[2] = 1;
          else if (order == 1)
            kerI[0] = -1, kerI[1] = 0, kerI[2] = 1;
        }
      else
        {
          int oldval, newval;
          kerI[0] = 1;
          for (i = 0; i < ksize; i++)
            kerI[i + 1] = 0;

          for (i = 0; i < ksize - order - 1; i++)
            {
              oldval = kerI[0];
              for (j = 1; j <= ksize; j++)
                {
                  newval = kerI[j] + kerI[j - 1];
                  kerI[j - 1] = oldval;
                  oldval = newval;
                }
            }

          for (i = 0; i < order; i++)
            {
              oldval = -kerI[0];
              for (j = 1; j <= ksize; j++)
                {
                  newval = kerI[j - 1] - kerI[j];
                  kerI[j - 1] = oldval;
                  oldval = newval;
                }
            }
        }

      for (i = 0; i < mask_size; ++i)
        {
          if (k == 0)
            dx[i] = kerI[i];
          else
            dy[i] = kerI[i];
        }
    }
  matrix_mult (dx, dy, sobel_x, mask_size, mask_size, false, false);
  matrix_mult (dy, dx, sobel_y, mask_size, mask_size, false, false);
  free (dx);
  free (dy);
  free (kerI);
}

static void
sobel (uint8_t *proc_arr, uint16_t *magnitude, uint16_t height, uint16_t width,
       uint8_t mask_size)
{
  int8_t *sobel_x = (int8_t *)calloc (mask_size * mask_size, sizeof (int8_t));
  int8_t *sobel_y = (int8_t *)calloc (mask_size * mask_size, sizeof (int8_t));
  int16_t *process_x_array
      = (int16_t *)calloc (width * height, sizeof (int16_t));
  int16_t *process_y_array
      = (int16_t *)calloc (width * height, sizeof (int16_t));

  sobel_operator (sobel_x, sobel_y, mask_size);
  image_conv_K_int8_t (proc_arr, sobel_x, process_x_array, height, width,
                       mask_size);
  image_conv_K_int8_t (proc_arr, sobel_y, process_y_array, height, width,
                       mask_size);

  // gradient magnitude with 1 norm
  for (uint32_t i = 0; i < (uint32_t)height * width; ++i)
    {
      magnitude[i]
          = (uint16_t)(abs (process_x_array[i]) + abs (process_y_array[i]))
            / 2;
    }

  free (process_x_array);
  free (process_y_array);
  free (sobel_x);
  free (sobel_y);
}
static void
prewitt (uint8_t *proc_arr, uint16_t *magnitude, uint16_t width,
         uint16_t height)
{
  uint8_t mask_size = 3;
  int8_t *prewitt = (int8_t *)calloc (mask_size * mask_size, sizeof (int8_t));
  int16_t *cov_result = (int16_t *)calloc (width * height, sizeof (int16_t));
  // gradient magnitude with 1 norm
  for (int8_t i = 0; i < 8; i++)
    {
      differential_operator (prewitt, (uint16_t)i * 45);
      image_conv_K_int8_t (proc_arr, prewitt, cov_result, height, width,
                           mask_size);
      for (int32_t j = 0; j < (int32_t)height * width; ++j)
        {
          magnitude[j] += (uint16_t)abs (cov_result[i]);
        }
    }
  for (int32_t j = 0; j < (int32_t)height * width; ++j)
    {
      magnitude[j] /= 8;
    }

  free (prewitt);
  free (cov_result);
}

void
image_gradient (uint8_t *image, uint16_t *magnitude, uint16_t height,
                uint16_t width, uint8_t mask_size, bool sobel_flag)
{
  // flag - true : sobel
  //	   - flase : prewitt
  uint16_t proc_size_w, proc_size_h;
  // Generate a buffer for Padding Image
  proc_size_w = width + (mask_size / 2) * 2;
  proc_size_h = height + (mask_size / 2) * 2;
  uint8_t *proc_arr
      = (uint8_t *)calloc (proc_size_w * proc_size_h, sizeof (uint8_t));

  Border_Reflect (proc_arr, image, height, width, mask_size);

  if (sobel_flag == true)
    {
      sobel (proc_arr, magnitude, height, width, mask_size);
    }
  else
    {
      prewitt (proc_arr, magnitude, height, width);
    }

  free (proc_arr);
}
void
image_prewitt (uint8_t *image, int16_t *result, uint16_t height,
               uint16_t width, uint16_t angle)
{

  int8_t *prewitt = (int8_t *)calloc (3 * 3, sizeof (int8_t));
  uint16_t proc_size_w, proc_size_h;
  uint8_t mask_size = 3;
  // Generate a buffer for Padding Image
  proc_size_w = width + (uint16_t)(mask_size / 2) * 2;
  proc_size_h = height + (uint16_t)(mask_size / 2) * 2;
  uint8_t *proc_arr
      = (uint8_t *)calloc (proc_size_w * proc_size_h, sizeof (uint8_t));

  Border_Reflect (proc_arr, image, height, width, mask_size);
  differential_operator (prewitt, angle);
  image_conv_K_int8_t (proc_arr, prewitt, result, height, width, 3);
  free (prewitt);
  free (proc_arr);
}