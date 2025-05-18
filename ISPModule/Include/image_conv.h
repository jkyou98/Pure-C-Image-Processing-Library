/**
 * @file image_conv.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototype of image convolution
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IMAGE_CONV_H_
#define IMAGE_CONV_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  /**
   * @brief Image convolution with float filter.
   *
   * @param[in] proc_arr image padding buffer
   * @param[in] filter image filter
   * @param[out] result result after image convolution
   * @param[in] height image height
   * @param[in] width image width
   * @param[in] mask_size mask size
   */
  void image_conv_K_f (uint8_t *proc_arr, float *filter, uint8_t *result,
                       uint16_t height, uint16_t width, uint8_t mask_size);
  /**
   * @brief Image convolution with int8_t filter.
   *
   * @param[in] proc_arr image padding buffer
   * @param[in] filter image filter
   * @param[out] result result after image convolution
   * @param[in] height image height
   * @param[in] width image width
   * @param[in] mask_size mask size
   */
  void image_conv_K_int8_t (uint8_t *proc_arr, int8_t *filter, int16_t *result,
                            uint16_t height, uint16_t width,
                            uint8_t mask_size);

#ifdef __cplusplus
}
#endif
#endif