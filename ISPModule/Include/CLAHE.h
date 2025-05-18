/**
 * @file CLAHE.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototype of CLAHE.
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef CLAHE_H_
#define CLAHE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>

  /// @brief Error codes for CLAHE
  typedef enum CLAHE_error_e
  {
    /// No error
    CLAHE_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    CLAHE_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    CLAHE_ERROR_COUNT
  } CLAHE_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for CLAHE module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *CLAHE_error_str (CLAHE_error_t err);

  /**
   * @brief Implement of clip limit adapated histogram equalization (CLAHE).
   *
   * @param IMG image struct
   * @param PARAM paramter struct of CLAHE
   */
  CLAHE_error_t CLAHE (ImageInfo *IMG, CLAHE_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif