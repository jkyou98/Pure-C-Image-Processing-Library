#include "IBR.h"
#include "Imagegradient.h"
#include "MinMax_Arr.h"
#include "MinMax_Mapping.h"
#include "param.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *
IMG_Crop_error_str (IBR_error_t err)
{
  const char *err_str = NULL;
  const char *const IBR_ERROR_STRS[] = {
    "IBR_ERROR_OK",
    "IBR_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= IBR_ERROR_COUNT)
    {
      goto done;
    }

  err_str = IBR_ERROR_STRS[err];

done:
  return err_str;
}

static void
IBR_uint8_t (uint8_t *image, uint8_t *proc_uint8_t, int16_t *proc_int16_t,
             uint8_t *result_uint8_t, uint16_t *sum_uint16_t, uint16_t width,
             uint16_t height)
{

  uint16_t i;
  uint8_t I;

  I = 0;
  while (I < 8)
    {

      // Original image prewitt gradient
      image_prewitt (image, proc_int16_t, height, width, I * 45);
      // normalization
      MinMax_int16_t (proc_int16_t, proc_uint8_t, width, height);
      // gradient proportion
      float w = 0;
      // image blending
      for (i = 0; i < (uint32_t)height * width; ++i)
        {
          result_uint8_t[i]
              = (uint8_t)((1 - w) * image[i] + w * proc_uint8_t[i]);
        }

      // Blending image prewitt gradient
      image_prewitt (result_uint8_t, proc_int16_t, height, width, I * 45);
      // normalization
      MinMax_int16_t (proc_int16_t, proc_uint8_t, width, height);

      // image estimation
      for (i = 0; i < (uint32_t)height * width; ++i)
        {
          proc_int16_t[i]
              = (int16_t)((1 / (1 - w))
                          * (result_uint8_t[i] - w * proc_uint8_t[i]));
        }

      // normalization
      MinMax_int16_t (proc_int16_t, result_uint8_t, width, height);
      // Sum of result with all angle
      for (i = 0; i < (uint32_t)height * width; ++i)
        {
          sum_uint16_t[i] += (uint16_t)result_uint8_t[i];
        }

      I++;
    }
  // 8-angle prewitt average
  for (i = 0; i < (uint32_t)height * width; ++i)
    {
      image[i] = (uint8_t)(sum_uint16_t[i] / 8.0);
    }
}

IBR_error_t
IBR (ImageInfo *IMG, IBR_param *PARAM)
{
  // pointer check
  if (IMG->image == NULL || IMG->image == NULL)
    return IBR_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      IBR_uint8_t ((uint8_t *)IMG->image, (uint8_t *)PARAM->proc_uint8_t,
                   (int16_t *)PARAM->proc_int16_t,
                   (uint8_t *)PARAM->result_uint8_t,
                   (uint16_t *)PARAM->sum_uint16_t, IMG->width, IMG->height);
      IMG->update_status = 2;
    }
  return IBR_ERROR_OK;
}