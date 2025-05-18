/**
 * @file CLAHE_padding.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of CLAHE_padding
 * @version 0.1
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "CLAHE_padding.h"
#include "param.h"
#include <stdint.h>
#include <stdio.h>

const char *
CLAHE_padding_error_str (CLAHE_padding_error_t err)
{
  const char *err_str = NULL;
  const char *const CLAHE_PADDING_ERROR_STRS[] = {
    "CLAHE_PADDING_ERROR_OK",
    "CLAHE_PADDING_ERROR_INVARG",
  };
  // Ensure error codes are within the valid array index range
  if (err >= CLAHE_PADDING_ERROR_COUNT)
    {
      goto done;
    }

  err_str = CLAHE_PADDING_ERROR_STRS[err];

done:
  return err_str;
}

CLAHE_padding_error_t
CLAHE_padding (ImageInfo *IMG, CLAHE_param *PARAM)
{
  // // pointer check
  // if (IMG->image == NULL)
  //   return CLAHE_PADDING_ERROR_INVARG;

  PARAM->image_padding_w = IMG->width, PARAM->image_padding_h = IMG->height;
  if (IMG->width % PARAM->grid_x != 0)
    {
      PARAM->padding_w = PARAM->grid_x - IMG->width % PARAM->grid_x;
      PARAM->image_padding_w = IMG->width + PARAM->padding_w;
      PARAM->b_width = PARAM->image_padding_w / PARAM->grid_x;
    }
  else
    {
      PARAM->b_width = IMG->width / PARAM->grid_x;
    }

  if (IMG->height % PARAM->grid_y != 0)
    {
      PARAM->padding_h = PARAM->grid_y - IMG->height % PARAM->grid_y;
      PARAM->image_padding_h = IMG->height + PARAM->padding_h;
      PARAM->b_height = (IMG->height + PARAM->padding_h) / PARAM->grid_y;
    }
  else
    {
      PARAM->b_height = IMG->height / PARAM->grid_y;
    }
  return CLAHE_PADDING_ERROR_OK;
}