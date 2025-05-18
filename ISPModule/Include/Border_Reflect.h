/**
 * @file Border_Reflect.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for border reflect
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BORDER_REFLECT_H_
#define BORDER_REFLECT_H_

#ifdef __cplusplus
extern "C"
{
#endif

  /// @brief Error codes for border reflect
  typedef enum Border_Reflect_error_e
  {
    /// No error
    BORDER_REFLECT_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    BORDER_REFLECT_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    BORDER_REFLECT_ERROR_COUNT
  } Border_Reflect_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   *@param[in]  err     a valid error code for Border_Reflect module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *Border_Reflect_error_str (Border_Reflect_error_t err);

#include <stdint.h>
  /**
   * @brief Image padding with border reflect method
   *
   * @param[in,out] proc_arr image padding buffer
   * @param[in] image  image buffer
   * @param[in] height image height
   * @param[in] width image width
   * @param[in] mask_size mask size of image filter
   */
  Border_Reflect_error_t Border_Reflect (uint8_t *proc_arr, uint8_t *image,
                                         uint16_t height, uint16_t width,
                                         uint8_t mask_size);
#ifdef __cplusplus
}
#endif
#endif