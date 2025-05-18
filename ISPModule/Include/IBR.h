/**
 * @file IBR.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for image blending recovery (IBR).
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IBR_H_
#define IBR_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>

  /// @brief Error codes for image crop
  typedef enum IBR_error_e
  {
    /// No error
    IBR_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    IBR_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    IBR_ERROR_COUNT
  } IBR_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for IBR module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *IBR_error_str (IBR_error_t err);

  /**
   * @brief Implement of IBR algorithm.
   *
   * @param IMG image struct
   * @param PARAM paramter struct of IBR
   */
  IBR_error_t IBR (ImageInfo *IMG, IBR_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif