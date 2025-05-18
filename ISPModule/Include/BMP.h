/**
 * @file BMP.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for BMP files read/write
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef BMP_H_
#define BMP_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  /// @brief Error codes for BMP R/W
  typedef enum BMP_error_e
  {
    /// BMP read no error
    BMP_READ_ERROR_OK = 0,
    /// BMP write invalid arguments (ex.NuLL pointer, parameter overflow)
    BMP_READ_ERROR_INVARG,
    /// BMP read no error
    BMP_WRITE_ERROR_OK,
    /// BMP write invalid arguments (ex.NuLL pointer, parameter overflow)
    BMP_WRITE_ERROR_INVARG,

    /// Total # of errors in this list (NOT AN ACTUAL ERROR CODE);
    /// NOTE: that for this to work, it assumes your first error code is value
    /// 0 and you let it naturally increment from there, as is done above,
    /// without explicitly altering any error values above
    BMP_ERROR_COUNT
  } BMP_error_t;
  /**
   * @brief      Function to get a printable string from an enum error type
   *@param[in]  err     a valid error code for BMP module
   * @return     A printable C string corresponding to the error code input
   * above, or NULL if an invalid error code was passed in
   */
  const char *BMP_error_str (BMP_error_t err);

  /**
   * @brief Read the 8bit gray bmp file from path "filename" and loads to
   * image with knowning image width and height.
   *
   * @param fileName bmp file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  BMP_error_t BMP_R_GRAY_8BIT (const char *fileName, uint8_t *image,
                               uint16_t width, uint16_t height);
  /**
   * @brief Write the 8bit gray bmp file to the path "filename"  with
   * knowning image width and height.
   *
   * @param fileName bmp file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  BMP_error_t BMP_W_GRAY_8BIT (const char *fileName, uint8_t *image,
                               uint16_t width, uint16_t height);

#ifdef __cplusplus
}
#endif
#endif