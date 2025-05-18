#include "param.h"
#include <stdlib.h>
#include <string.h>

void *
memeryAllocate (ISPParam_st *ISPParam)
{
  // image
  ISPParam->IMG_Info.image = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (uint8_t));
  memset (ISPParam->IMG_Info.image, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (uint8_t));
  // BG image
  ISPParam->BG_IMG_8Bit = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (uint8_t));
  memset (ISPParam->BG_IMG_8Bit, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (uint8_t));

  // Image Substraction
  ISPParam->IMG_substration = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (int16_t));
  memset (ISPParam->IMG_substration, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (int16_t));

  // DOG
  ISPParam->DOG_Param.image_blur1 = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (uint8_t));
  memset (ISPParam->DOG_Param.image_blur1, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (uint8_t));
  ISPParam->DOG_Param.image_blur2 = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (uint8_t));
  memset (ISPParam->DOG_Param.image_blur2, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (uint8_t));
  ISPParam->DOG_Param.DOG_raw = malloc (
      ISPParam->IMG_Info.width * ISPParam->IMG_Info.height * sizeof (int16_t));
  memset (ISPParam->DOG_Param.DOG_raw, 0,
          ISPParam->IMG_Info.width * ISPParam->IMG_Info.height
              * sizeof (int16_t));
  ISPParam->DOG_Param.Gauss_filter
      = malloc (ISPParam->DOG_Param.GaussianFilterSize
                * ISPParam->DOG_Param.GaussianFilterSize * sizeof (float));
  memset (ISPParam->DOG_Param.Gauss_filter, 0,
          ISPParam->DOG_Param.GaussianFilterSize
              * ISPParam->DOG_Param.GaussianFilterSize * sizeof (float));
  ISPParam->DOG_Param.image_padding
      = malloc (ISPParam->DOG_Param.image_padding_w
                * ISPParam->DOG_Param.image_padding_h * sizeof (uint8_t));
  memset (ISPParam->DOG_Param.image_padding, 0,
          ISPParam->DOG_Param.image_padding_w
              * ISPParam->DOG_Param.image_padding_h * sizeof (uint8_t));

  // OC
  ISPParam->OC_Param.image_padding
      = malloc (ISPParam->OC_Param.image_padding_w
                * ISPParam->OC_Param.image_padding_h * sizeof (uint8_t));
  memset (ISPParam->OC_Param.image_padding, 0,
          ISPParam->OC_Param.image_padding_w
              * ISPParam->OC_Param.image_padding_h * sizeof (uint8_t));
  ISPParam->OC_Param.hist = malloc (256 * sizeof (uint32_t));
  memset (ISPParam->OC_Param.hist, 0, 256 * sizeof (uint32_t));

  // MF
  ISPParam->MF_Param.image_padding
      = malloc (ISPParam->MF_Param.image_padding_w
                * ISPParam->MF_Param.image_padding_h * sizeof (uint8_t));
  memset (ISPParam->MF_Param.image_padding, 0,
          ISPParam->MF_Param.image_padding_w
              * ISPParam->MF_Param.image_padding_h * sizeof (uint8_t));

  // CLAHE
  ISPParam->CLAHE_Param.CDF_map
      = malloc (ISPParam->CLAHE_Param.grid_x * ISPParam->CLAHE_Param.grid_y
                * 256 * sizeof (uint32_t));
  memset (ISPParam->CLAHE_Param.CDF_map, 0,
          ISPParam->CLAHE_Param.grid_x * ISPParam->CLAHE_Param.grid_y * 256
              * sizeof (uint32_t));
  ISPParam->CLAHE_Param.image_padding
      = malloc (ISPParam->CLAHE_Param.image_padding_h
                * ISPParam->CLAHE_Param.image_padding_w * sizeof (uint8_t));
  memset (ISPParam->CLAHE_Param.image_padding, 0,
          ISPParam->CLAHE_Param.image_padding_h
              * ISPParam->CLAHE_Param.image_padding_w * sizeof (uint8_t));

  // IBR
  ISPParam->IBR_Param.proc_uint8_t = malloc (
      ISPParam->IMG_Info.height * ISPParam->IMG_Info.width * sizeof (uint8_t));
  memset (ISPParam->IBR_Param.proc_uint8_t, 0,
          ISPParam->IMG_Info.height * ISPParam->IMG_Info.width
              * sizeof (uint8_t));
  ISPParam->IBR_Param.proc_int16_t = malloc (
      ISPParam->IMG_Info.height * ISPParam->IMG_Info.width * sizeof (int16_t));
  memset (ISPParam->IBR_Param.proc_int16_t, 0,
          ISPParam->IMG_Info.height * ISPParam->IMG_Info.width
              * sizeof (int16_t));
  ISPParam->IBR_Param.result_uint8_t = malloc (
      ISPParam->IMG_Info.height * ISPParam->IMG_Info.width * sizeof (uint8_t));
  memset (ISPParam->IBR_Param.result_uint8_t, 0,
          ISPParam->IMG_Info.height * ISPParam->IMG_Info.width
              * sizeof (uint8_t));
  ISPParam->IBR_Param.sum_uint16_t
      = malloc (ISPParam->IMG_Info.height * ISPParam->IMG_Info.width
                * sizeof (uint16_t));
  memset (ISPParam->IBR_Param.sum_uint16_t, 0,
          ISPParam->IMG_Info.height * ISPParam->IMG_Info.width
              * sizeof (uint16_t));

  // HE
  ISPParam->HE_Param.cdf
      = malloc (ISPParam->HE_Param.bins * sizeof (uint32_t));
  memset (ISPParam->HE_Param.cdf, 0,
          ISPParam->HE_Param.bins * sizeof (uint32_t));
  ISPParam->HE_Param.hist = malloc (256 * sizeof (uint32_t));
  memset (ISPParam->HE_Param.hist, 0, 256 * sizeof (uint32_t));

  if (!ISPParam->IMG_Info.image || !ISPParam->BG_IMG_8Bit
      || !ISPParam->IMG_substration || !ISPParam->DOG_Param.image_blur1
      || !ISPParam->DOG_Param.image_blur2 || !ISPParam->DOG_Param.DOG_raw
      || !ISPParam->DOG_Param.Gauss_filter
      || !ISPParam->DOG_Param.image_padding
      || !ISPParam->OC_Param.image_padding || !ISPParam->OC_Param.hist
      || !ISPParam->MF_Param.image_padding || !ISPParam->CLAHE_Param.CDF_map
      || !ISPParam->CLAHE_Param.image_padding
      || !ISPParam->IBR_Param.proc_uint8_t || !ISPParam->IBR_Param.proc_int16_t
      || !ISPParam->IBR_Param.result_uint8_t
      || !ISPParam->IBR_Param.sum_uint16_t)
    return NULL;
}

void
memeryFree (ISPParam_st *ISPParam)
{
  free (ISPParam->IMG_Info.image);
  free (ISPParam->BG_IMG_8Bit);
  free (ISPParam->IMG_substration);
  free (ISPParam->DOG_Param.image_blur1);
  free (ISPParam->DOG_Param.image_blur2);
  free (ISPParam->DOG_Param.DOG_raw);
  free (ISPParam->DOG_Param.Gauss_filter);
  free (ISPParam->DOG_Param.image_padding);
  free (ISPParam->OC_Param.image_padding);
  free (ISPParam->OC_Param.hist);
  free (ISPParam->MF_Param.image_padding);
  free (ISPParam->CLAHE_Param.CDF_map);
  free (ISPParam->CLAHE_Param.image_padding);
  free (ISPParam->IBR_Param.proc_uint8_t);
  free (ISPParam->IBR_Param.proc_int16_t);
  free (ISPParam->IBR_Param.result_uint8_t);
  free (ISPParam->IBR_Param.sum_uint16_t);
  free (ISPParam->HE_Param.cdf);
}