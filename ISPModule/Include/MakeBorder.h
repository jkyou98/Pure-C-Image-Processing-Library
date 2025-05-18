/**
 * @file MakeBorder.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes of makeborder.
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MAKEBORDER_H_
#define MAKEBORDER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

  /// @brief Error codes for CLAHE
  typedef enum MakeBorder_error_e
  {
    /// No error
    MAKEBORDER_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    MAKEBORDER_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    MAKEBORDER_ERROR_COUNT
  } MakeBorder_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for MakeBorder module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *MakeBorder_error_str (MakeBorder_error_t err);

  /**
   * @brief Padding border with requested paramter
   *
   * @param[in] image image buffer
   * @param[out] image_padding image padding buffer
   * @param[in] width image width
   * @param[in] height image height
   * @param[in] top requested padding height at top area
   * @param[in] bottom requested padding height at bottom area
   * @param[in] left requested padding width at left area
   * @param[in] right requested padding width at right area
   */
  MakeBorder_error_t MakeBorder (uint8_t *image, uint8_t *image_padding,
                                 uint16_t width, uint16_t height, uint8_t top,
                                 uint8_t bottom, uint8_t left, uint8_t right);
#ifdef __cplusplus
}
#endif
#endif