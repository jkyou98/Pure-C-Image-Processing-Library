/**
 * @file RAW.c
 * @author your name (you@domain.com)
 * @brief Source code of raw files read/write
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "RAW.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void
RAW_READ_uint16_t (const char *fileName, uint16_t *image, uint16_t width,
                   uint16_t height)
{
  // Open the file for reading in binary mode
  FILE *imageFile = fopen (fileName, "rb");
  // read binary file
  fread (image, sizeof (*image), width * height, imageFile);
  fclose (imageFile);
}

void
RAW_WRITE_uint16_t (const char *fileName, uint16_t *image, uint16_t width,
                    uint16_t height)
{
  // Open the file for reading in binary mode
  FILE *outputFile = fopen (fileName, "wb+");
  // read binary file
  fwrite (image, sizeof (*image), width * height, outputFile);
  fclose (outputFile);
}
void
RAW_READ_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                  uint16_t height)
{
  // Open the file for reading in binary mode
  FILE *imageFile = fopen (fileName, "rb");
  // read binary file
  fread (image, sizeof (*image), width * height, imageFile);
  fclose (imageFile);
}

void
RAW_WRITE_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                   uint16_t height)
{
  // Open the file for reading in binary mode
  FILE *outputFile = fopen (fileName, "wb+");
  // read binary file
  fwrite (image, sizeof (*image), width * height, outputFile);
  fclose (outputFile);
}

void
CSV_READ_uint8_t (const char *fileName, uint8_t *image, uint16_t width,
                  uint16_t height)
{
  // Open the file for reading
  // printf ("ImagePath: %s\n", fileName);
  FILE *outputFile = fopen (fileName, "r");
  uint16_t read_width = width * 5;
  char *row = malloc (read_width * sizeof (char));
  memset (row, 0, read_width * sizeof (char));
  char *token;
  int RowLength;
  int ColLength;

  ColLength = 0;
  while (fgets (row, read_width, outputFile))
    {
      token = strtok (row, ",");
      RowLength = 0;
      while (token != NULL)
        {
          image[ColLength * width + RowLength] = atoi (token);
          token = strtok (NULL, ",");
          RowLength++;
          if (RowLength == width)
            break;
        }
      ColLength++;
    }

  fclose (outputFile);
  free (row);
}
