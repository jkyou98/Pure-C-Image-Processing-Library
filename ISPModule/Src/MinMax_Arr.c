/**
 * @file MinMax_Arr.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source file of MinMax_Arr
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
uint8_t
FindMinEle_uint8_t (uint8_t *arr, uint16_t n)
{
  uint16_t i;
  uint8_t min;

  // fine minimum element in array
  min = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) < min)
        {
          min = *(arr + i);
        }
    }
  return min;
}

uint8_t
FindMaxEle_uint8_t (uint8_t *arr, uint16_t n)
{
  uint16_t i;
  uint8_t max;

  // fine maximum element
  max = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) > max)
        {
          max = *(arr + i);
        }
    }
  return max;
}

uint16_t
FindMinEle_uint16_t (uint16_t *arr, uint16_t n)
{
  uint16_t i;
  uint16_t min;

  // fine minimum element in array
  min = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) < min)
        {
          min = *(arr + i);
        }
    }
  return min;
}

uint16_t
FindMaxEle_uint16_t (uint16_t *arr, uint16_t n)
{
  uint16_t i;
  uint16_t max;

  // fine maximum element
  max = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) > max)
        {
          max = *(arr + i);
        }
    }
  return max;
}

int16_t
FindMinEle_int16_t (int16_t *arr, uint16_t n)
{
  uint16_t i;
  int16_t min;

  // fine minimum element in array
  min = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) < min)
        {
          min = *(arr + i);
        }
    }
  return min;
}

int16_t
FindMaxEle_int16_t (int16_t *arr, uint16_t n)
{
  uint16_t i;
  int16_t max;

  // fine maximum element
  max = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) > max)
        {
          max = *(arr + i);
        }
    }
  return max;
}

float
FindMinEle_f (float *arr, uint16_t n)
{
  uint16_t i;
  float min;

  // fine minimum element in array
  min = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) < min)
        {
          min = *(arr + i);
        }
    }
  return min;
}

float
FindMaxEle_f (float *arr, uint16_t n)
{
  uint16_t i;
  float max;

  // fine maximum element
  max = *arr;

  for (i = 0; i < n; i++)
    {
      if (*(arr + i) > max)
        {
          max = *(arr + i);
        }
    }
  return max;
}
