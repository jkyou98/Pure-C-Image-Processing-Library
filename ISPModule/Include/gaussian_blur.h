/**
 * @file gaussian_blur.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for Gaussian blur
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef GAUSSIAN_BLUR_H_
#define GAUSSIAN_BLUR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

  /// @brief Error codes for image crop
  typedef enum gaussian_blur_error_e
  {
    /// No error
    GAUSSIAN_BLUR_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    GAUSSIAN_BLUR_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    GAUSSIAN_BLUR_ERROR_COUNT
  } gaussian_blur_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for gaussian_blur module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *gaussian_blur_error_str (gaussian_blur_error_t err);

  /**
   * @brief Image of Gaussain blur with requested radius
   *
   * @param[in] image  image buffer
   * @param[in] image_padding image padding buffer
   * @param[in] Gauss_filter Gaussain filter buffer
   * @param[out] image_blur image blur buffer
   * @param[in] height image height
   * @param[in] width image width
   * @param[in] radius Gaussain blur radius
   */
  gaussian_blur_error_t gaussian_blur (uint8_t *image, uint8_t *image_padding,
                                       float *Gauss_filter,
                                       uint8_t *image_blur, uint16_t height,
                                       uint16_t width, uint8_t radius);

#ifdef __cplusplus
}
#endif
#endif