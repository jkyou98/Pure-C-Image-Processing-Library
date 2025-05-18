/**
 * @file HistEqualize.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototype of histogram equalization.
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef HISTEQUALIZE_H_
#define HISTEQUALIZE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>
  /// @brief Error codes for histogram equalization
  typedef enum HistEqualize_error_e
  {
    /// No error
    HISTEQUALIZE_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    HISTEQUALIZE_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    HISTEQUALIZE_ERROR_COUNT
  } HistEqualize_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for HistEqualize module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *HistEqualize_error_str (HistEqualize_error_t err);

  /**
   * @brief Implement of histogram equalization
   *
   * @param IMG image struct
   * @param PARAM paramter struct of histogram equalization
   */
  HistEqualize_error_t HistEqualize (ImageInfo *IMG,
                                     HistEqualize_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif