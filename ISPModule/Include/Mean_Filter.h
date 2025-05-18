/**
 * @file Mean_Filter.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes of mean filter
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MEAN_FILTER_H_
#define MEAN_FILTER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include "param.h"
#include <stdint.h>

  /// @brief Error codes for image crop
  typedef enum Mean_Filter_error_e
  {
    /// No error
    MEAN_FILTER_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    MEAN_FILTER_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    MEAN_FILTER_ERROR_COUNT
  } Mean_Filter_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for Mean_Filter module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *Mean_Filter_error_str (Mean_Filter_error_t err);

  /**
   * @brief Compute the mean filter for denoising with parameter PARAM
   *
   * @param IMG image struct
   * @param PARAM paramter struct of mean filter
   */
  Mean_Filter_error_t Mean_Filter (ImageInfo *IMG, Mean_Filter_param *PARAM);
#ifdef __cplusplus
}
#endif
#endif