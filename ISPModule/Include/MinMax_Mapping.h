/**
 * @file MinMax_Mapping.h
 * @author StanleyHsu (jkyou98@gmail.com)
 * @brief Function prototypes of min-max mapping
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MINMAX_MAPPING_H_
#define MINMAX_MAPPING_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  void MinMax_int16_t (int16_t *input, uint8_t *result, uint16_t width,
                       uint16_t height);
  void MinMax_uint16_t (uint16_t *input, uint8_t *result, uint16_t width,
                        uint16_t height);
#ifdef __cplusplus
}
#endif
#endif