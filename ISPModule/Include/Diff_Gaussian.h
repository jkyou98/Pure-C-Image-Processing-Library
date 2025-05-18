/**
 * @file Diff_Gaussian.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for difference of gaussian
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DIFF_GAUSSIAN_H_
#define DIFF_GAUSSIAN_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>
  /// @brief Error codes for image crop
  typedef enum Diff_Gaussian_error_e
  {
    /// No error
    DIFF_GAUSSIAN_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    DIFF_GAUSSIAN_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    DIFF_GAUSSIAN_ERROR_COUNT
  } Diff_Gaussian_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for Diff_Gaussian module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *Diff_Gaussian_error_str (Diff_Gaussian_error_t err);

  /**
   * @brief Compute difference of gaussian image.
   *
   * @param IMG image struct
   * @param PARAM paramter struct of difference of gaussian
   */
  Diff_Gaussian_error_t Diff_Gaussian (ImageInfo *IMG,
                                       Diff_Gaussian_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif
