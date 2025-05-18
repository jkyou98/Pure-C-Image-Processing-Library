/**
 * @file CLAHE_padding.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototype of CLAHE_padding.
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CLAHE_PADDING_H_
#define CLAHE_PADDING_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>

  /// @brief Error codes for CLAHE_padding
  typedef enum CLAHE_padding_error_e
  {
    /// No error
    CLAHE_PADDING_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    CLAHE_PADDING_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    CLAHE_PADDING_ERROR_COUNT
  } CLAHE_padding_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for CLAHE_padding module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *CLAHE_PADDING_error_str (CLAHE_padding_error_t err);

  /**
   * @brief Compute image padding size for CLAHE
   *
   * @param IMG image struct
   * @param PARAM parameter struct of CLAHE
   */
  CLAHE_padding_error_t CLAHE_padding (ImageInfo *IMG, CLAHE_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif