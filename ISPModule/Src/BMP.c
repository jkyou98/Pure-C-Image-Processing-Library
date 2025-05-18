/**
 * @file BMP.c
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Source code of BMP Read/Write.
 * @version 0.1
 * @date 2022-01-13
 * @sa https://charlottehong.blogspot.com/2017/06/c-raw-bmp.html
 * @copyright Copyright (c) 2022
 *
 */

#include "BMP.h"

#include <errno.h>
#include <stdint.h>
#include <stdio.h>

#pragma pack(2)

struct BmpFileHeader
{
  uint16_t bfTybe;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
};
struct BmpInfoHeader
{
  uint32_t biSize;
  uint32_t biWidth;
  uint32_t biHeight;
  uint16_t biPlanes; ///< 1=default, 0=custom
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  uint32_t biXPelsPerMeter; ///< 72dpi=2835, 96dpi=3780
  uint32_t biYPelsPerMeter; ///<  120dpi=4724, 300dpi=11811
  uint32_t biClrUsed;
  uint32_t biClrImportant;
};
#pragma pack()

#define BMP_Image_data_offset 1078 // 8bit BMP data offset


const char *
BMP_error_str (BMP_error_t err)
{
  const char *err_str = NULL;
  const char *const BMP_ERROR_STRS[] = {
    "BMP_READ_ERROR_OK",
    "BMP_READ_ERROR_INVARG",
    "BMP_WRITE_ERROR_OK",
    "BMP_WRITE_ERROR_INVARG",

  };
  // Ensure error codes are within the valid array index range
  if (err >= BMP_ERROR_COUNT)
    {
      goto done;
    }

  err_str = BMP_ERROR_STRS[err];

done:
  return err_str;
}

BMP_error_t
BMP_R_GRAY_8BIT (const char *fileName, uint8_t *image, uint16_t width,
                 uint16_t height)
{
  FILE *imageFile = NULL;
  imageFile = fopen (fileName, "rb+");
  // read file check
  if (imageFile == NULL)
    return BMP_READ_ERROR_INVARG;

  fseek (imageFile, BMP_Image_data_offset, SEEK_SET);

  uint8_t align = (width * 3) % 4;
  // reading raw data
  for (int16_t j = height - 1; j >= 0; --j)
    {
      for (uint16_t i = 0; i < width; ++i)
        {
          fread (&image[j * width + i], sizeof (*image), 1, imageFile);
        }
      fseek (imageFile, (long)align, SEEK_CUR);
    }
  fclose (imageFile);
  return BMP_READ_ERROR_OK;
}

BMP_error_t
BMP_W_GRAY_8BIT (const char *fileName, uint8_t *image, uint16_t width,
                 uint16_t height)
{
  struct BmpFileHeader file_h = {
    .bfTybe = 0x4d42,
    .bfReserved1 = 0,
    .bfReserved2 = 0,
    .bfOffBits = 54,
  };
  file_h.bfSize = file_h.bfOffBits + width * height;
  file_h.bfSize += 1024, file_h.bfOffBits += 1024;
  struct BmpInfoHeader info_h = {
    .biSize = 40,
    .biPlanes = 1,
    .biCompression = 0,
    .biXPelsPerMeter = 0,
    .biYPelsPerMeter = 0,
    .biClrUsed = 0,
    .biClrImportant = 0,
  };
  info_h.biWidth = width;
  info_h.biHeight = height;
  info_h.biBitCount = 8;
  info_h.biSizeImage = width * height;
  info_h.biClrUsed = 256;

  FILE *imageFile = NULL;
  imageFile = fopen (fileName, "wb+");
  // write file check
  if (imageFile == NULL)
    return BMP_WRITE_ERROR_INVARG;

  // writing BMP header
  fwrite ((uint8_t *)&file_h, sizeof (uint8_t), sizeof (file_h), imageFile);
  fwrite ((uint8_t *)&info_h, sizeof (uint8_t), sizeof (info_h), imageFile);

  for (uint16_t i = 0; i < 256; ++i)
    {
      uint8_t c = i;
      fwrite ((uint8_t *)&c, sizeof (uint8_t), sizeof (uint8_t), imageFile);
      fwrite ((uint8_t *)&c, sizeof (uint8_t), sizeof (uint8_t), imageFile);
      fwrite ((uint8_t *)&c, sizeof (uint8_t), sizeof (uint8_t), imageFile);
      fwrite ("", sizeof (uint8_t), sizeof (uint8_t), imageFile);
    }

  uint8_t align = (uint8_t)((width * 3) % 4);
  // writing raw data
  for (int16_t j = height - 1; j >= 0; --j)
    {
      for (uint16_t i = 0; i < width; ++i)
        {
          fwrite (&image[j * width + i], sizeof (*image), 1, imageFile);
        }
      for (uint8_t i = 0; i < align; ++i)
        {
          fwrite ("", sizeof (*image), 1, imageFile);
        }
    }
  fclose (imageFile);
  return BMP_WRITE_ERROR_OK;
}