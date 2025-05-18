/**
 * @file I_Hist_er.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for image histogram with empirical rule
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef I_HIST_ER_H_
#define I_HIST_ER_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

  /// @brief Error codes for image histogram with empirical rule
  typedef enum I_Hist_er_error_e
  {
    ///I_Hist_er no error
    I_HIST_ER_ERROR_OK = 0,
    ///I_Hist_er invalid arguments (ex.NuLL pointer, parameter overflow)
    I_HIST_ER_ERROR_INVARG,
    ///I_Hist_er_mean no error
    I_HIST_ER_MEAN_ERROR_OK,
    ///I_Hist_er_mean invalid arguments (ex.NuLL pointer, parameter overflow)
    I_HIST_ER_MEAN_ERROR_INVARG,

    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    I_HIST_ER_ERROR_COUNT
  } I_Hist_er_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for I_Hist_er module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *I_Hist_er_error_str (I_Hist_er_error_t err);

  /**
   * @brief Find the upper/lower bound of the image with sigma ratio (i.e. +- 3
   * sigma or 2 sigma)
   *
   * @param[in] image image buffer
   * @param[in] height image height
   * @param[in] width image width
   * @param[out] lower_B lower bound of by requested sigma ratio
   * @param[out] upper_B upper bound of by requested sigma ratio
   * @param[in] sigma_ratio sigma ratio of empirical rule
   */
  I_Hist_er_error_t I_Hist_er (uint8_t *image, uint16_t height, uint16_t width,
                               uint8_t *lower_B, uint8_t *upper_B,
                               float sigma_ratio);
  I_Hist_er_error_t I_Hist_er_mean (uint8_t *image, uint32_t *hist,
                                    uint16_t height, uint16_t width,
                                    uint8_t *lower_B, uint8_t *upper_B,
                                    float f_percent);
#ifdef __cplusplus
}
#endif
#endif