/**
 * @file Imagegradient.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef IMAGEGRADIENT_H_
#define IMAGEGRADIENT_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <stdint.h>
  void image_gradient (uint8_t *image, uint16_t *magnitude, uint16_t height,
                       uint16_t width, uint8_t mask_size, bool sobel_flag);
  void image_prewitt (uint8_t *image, int16_t *result, uint16_t height,
                      uint16_t width, uint16_t angle);
#ifdef __cplusplus
}
#endif
#endif