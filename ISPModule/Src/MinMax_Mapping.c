#include "MinMax_Mapping.h"
#include "MinMax_Arr.h"
#include <stdint.h>
#include <stdio.h>

void
MinMax_int16_t (int16_t *input, uint8_t *result, uint16_t width,
                uint16_t height)
{
  int16_t min, max;
  // find maximum & minimum element
  min = FindMinEle_int16_t (input, height * width);
  max = FindMaxEle_int16_t (input, height * width);
  // Normalizing to [0, 255]
  for (uint32_t i = 0; i < (uint32_t)height * width; i++)
    {
      result[i] = (uint8_t)(((input[i] - min) * 255) / (max - min));
    }
}

void
MinMax_uint16_t (uint16_t *input, uint8_t *result, uint16_t width,
                 uint16_t height)
{
  uint16_t min, max;
  // find maximum & minimum element
  min = FindMinEle_uint16_t (input, height * width);
  max = FindMaxEle_uint16_t (input, height * width);
  // Normalizing to [0, 255]
  for (uint32_t i = 0; i < (uint32_t)height * width; i++)
    {
      result[i] = (uint8_t)(((input[i] - min) * 255) / (max - min));
    }
}