/**
 * @file MinMax_Arr.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for finding min/max value of array
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MINMAX_ARR_H_
#define MINMAX_ARR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  uint8_t FindMinEle_uint8_t (uint8_t *arr, uint16_t n);
  uint8_t FindMaxEle_uint8_t (uint8_t *arr, uint16_t n);
  uint16_t FindMinEle_uint16_t (uint16_t *arr, uint16_t n);
  uint16_t FindMaxEle_uint16_t (uint16_t *arr, uint16_t n);
  int16_t FindMinEle_int16_t (int16_t *arr, uint16_t n);
  int16_t FindMaxEle_int16_t (int16_t *arr, uint16_t n);
  float FindMinEle_f (float *arr, uint16_t n);
  float FindMaxEle_f (float *arr, uint16_t n);
#ifdef __cplusplus
}
#endif
#endif