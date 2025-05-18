/**
 * @file HistEqualize.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of HistEqualize
 * @version 0.1
 * @date 2022-01-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "HistEqualize.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char *
HistEqualize_error_str (HistEqualize_error_t err)
{
  const char *err_str = NULL;
  const char *const HISTEQUALIZE_ERROR_STRS[] = {
    "HISTEQUALIZE_ERROR_OK",
    "HISTEQUALIZE_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= HISTEQUALIZE_ERROR_COUNT)
    {
      goto done;
    }

  err_str = HISTEQUALIZE_ERROR_STRS[err];

done:
  return err_str;
}

static void
HistEqualize_uint8_t (uint8_t *image, uint32_t *hist, uint32_t *cdf,
                      uint16_t width, uint16_t height, uint8_t HE_min,
                      uint8_t HE_max, uint16_t bins)
{
  // note: width of bin = 1 for the function

  // image histogram
  for (uint32_t i = 0; i < (uint32_t)width * height; ++i)
    {
      if (image[i] > HE_max || image[i] < HE_min)
        continue;
      int idx_t = image[i] - HE_min;
      hist[idx_t]++;
    }

  // cdf count
  cdf[0] = hist[0];
  for (uint16_t bin_cdf_ix = 1; bin_cdf_ix < bins; ++bin_cdf_ix)
    {
      for (uint16_t bin_ix = 0; bin_ix < bin_cdf_ix + 1; ++bin_ix)
        {
          cdf[bin_cdf_ix] += hist[bin_ix];
        }
    }

  // find HE_minimum non-zero bin of cdf
  uint8_t k = 0;
  while (!cdf[k])
    ++k;

  // histogram equalization
  uint8_t temp;
  for (uint32_t i = 0; i < (uint32_t)height * width; ++i)
    {

      if (image[i] > HE_max || image[i] < HE_min)
        continue;

      temp = image[i];
      for (uint16_t bin_ix = 0; bin_ix < bins; ++bin_ix)
        {
          if (image[i] < (bin_ix + 1) + HE_min && image[i] >= bin_ix + HE_min)
            {
              temp = (uint8_t)bin_ix;
            }
        }

      image[i] = (uint8_t)((float)(cdf[temp] - cdf[k]) * (HE_max - HE_min)
                               / (cdf[bins - 1] - cdf[k])
                           + HE_min);
    }
}
HistEqualize_error_t
HistEqualize (ImageInfo *IMG, HistEqualize_param *PARAM)
{
  // pointer check
  if (IMG->image == NULL || IMG->image == NULL)
    return HISTEQUALIZE_ERROR_INVARG;
  if (IMG->bit == 8)
    {
      HistEqualize_uint8_t ((uint8_t *)IMG->image, (uint32_t *)PARAM->hist,
                            (uint32_t *)PARAM->cdf, IMG->width, IMG->height,
                            PARAM->HE_min, PARAM->HE_max, PARAM->bins);
      IMG->update_status = 2;
    }
  return HISTEQUALIZE_ERROR_OK;
}