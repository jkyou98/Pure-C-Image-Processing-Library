/**
 * @file Outlier_Correct.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for outliers correction
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef OUTLIER_CORRECT_H_
#define OUTLIER_CORRECT_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>

  /// @brief Error codes for outliers correction
  typedef enum Outlier_Correct_error_e
  {
    /// No error
    OUTLIER_CORRECT_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    OUTLIER_CORRECT_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    OUTLIER_CORRECT_ERROR_COUNT
  } Outlier_Correct_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for Outlier_Correct module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *Outlier_Correct_error_str (Outlier_Correct_error_t err);

  /**
   * @brief Remove outliers of image with parameter PARAM.
   *
   * @param IMG image struct
   * @param PARAM paramter struct of outliers correction
   */
  Outlier_Correct_error_t Outlier_Correct (ImageInfo *IMG,
                                           Outlier_Correct_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif