/**
 * @file ImageStat.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for image status
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IMAGESTAT_H_
#define IMAGESTAT_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

  /// @brief Error codes for image status
  typedef enum ImageStat_error_e
  {
    /// No error
    IMAGESTAT_ERROR_OK = 0,
    /// Invalid arguments (ex.NuLL pointer, parameter overflow)
    IMAGESTAT_ERROR_INVARG,
    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    IMAGESTAT_ERROR_COUNT
  } ImageStat_error_t;

  /**
   * @brief      Function to get a printable string from an enum error type
   * @param[in]  err   a valid error code for ImageStat module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *ImageStat_error_str (ImageStat_error_t err);

  /**
   * @brief Calculate image status
   *
   * @param[in] image image buffer
   * @param[in] height image height
   * @param[in] width image width
   * @param[out] Mean mean pixel value of image
   * @param[out] Std standard deviation of image
   * @param[out] sigma_min measurement of minimun sigma
   * @param[out] sigma_max measurement of maximun sigma
   * @param[out] sigma_total measurement of sigma range
   * @param[out] Min minimun pixel value
   * @param[out] Max maximun pixel value
   */
  ImageStat_error_t ImageStat (uint8_t *image, uint16_t height, uint16_t width,
                               float *Mean, float *Std, float *sigma_min,
                               float *sigma_max, float *sigma_total,
                               uint8_t *Min, uint8_t *Max);
#ifdef __cplusplus
}
#endif
#endif