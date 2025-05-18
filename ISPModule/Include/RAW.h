/**
 * @file RAW.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes for raw files read/write
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef RAW_H_
#define RAW_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  /**
   * @brief Read the 16bit raw file from path "filename" and loads to
   * image with knowning image width and height
   *
   * @param fileName raw file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  void RAW_READ_uint16_t (const char *fileName, uint16_t *image,
                          uint16_t width, uint16_t height);
  /**
   * @brief Write the 16bit raw file to the path "filename"  with
   * knowning image width and height.
   *
   * @param fileName bmp file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  void RAW_WRITE_uint16_t (const char *fileName, uint16_t *image,
                           uint16_t width, uint16_t height);
  /**
   * @brief Read the 8bit raw file from path "filename" and loads to
   * image with knowning image width and height
   *
   * @param fileName raw file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  void RAW_READ_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                         uint16_t height);
  /**
   * @brief Write the 8bit raw file to the path "filename"  with
   * knowning image width and height.
   *
   * @param fileName bmp file path
   * @param image image buffer
   * @param width image width
   * @param height image height
   */
  void RAW_WRITE_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                          uint16_t height);

  void CSV_READ_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                         uint16_t height);
#ifdef __cplusplus
}
#endif
#endif