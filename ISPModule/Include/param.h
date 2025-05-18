#ifndef PARAM_H_
#define PARAM_H_

#define GAUSSAIN_RADIUS_1 1
#define GAUSSAIN_RADIUS_2 10
#define OC_SF_SIZE 3
#define OC_MAX_ITER 6
#define MF_SIZE 3
#define CLAHE_GRID_X 16
#define CLAHE_GRID_Y 16
#define CLAHE_S_LIMIT 15
#define HE_MIN 0
#define HE_MAX 255

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
  /**
   * A structure to represent image basic info.
   */
  typedef struct ImageInfo_t
  {
    /**
     * @name Buffer
     */
    /*@{*/
    void *image;        /**< pointer which point to image buffer */
    void *output_image; /**< pointer which point to output buffer */
    /*@}*/
    /**
     * @name Info
     */
    /*@{*/
    uint16_t width;        /**<  image width */
    uint16_t height;       /**< image height*/
    uint8_t bit;           /**< image bit*/
    uint8_t update_status; /**< 0:original,
                            *1:*image updated,
                            *2:save to *output_image */
    /*@}*/
  } ImageInfo;
  /**
   * A structure to represent differential of Gaussian parameter info.
   */
  typedef struct Diff_Gaussian_param_t
  {
    /**
     * @name Buffer
     */
    /*@{*/
    void *image_padding; /**<pointer which point to image padding buffer*/
    void *Gauss_filter;  /**< pointer which point to gaussian filter buffer */
    void *image_blur1;   /**< first pointer which point to image blur buffer */
    void *image_blur2; /**< second pointer which point to image blur buffer */
    void *DOG_raw; /**< pointer which point to DOG raw computation buffer */
    /*@}*/
    /**
     * @name Parameters
     */
    /*@{*/
    uint8_t radius1; /**< first radius of gaussain filter */
    uint8_t radius2; /**< second radius of gaussain filter */
    uint8_t GaussianFilterSize;
    uint16_t image_padding_w;
    uint16_t image_padding_h;
    /*@}*/
  } Diff_Gaussian_param;
  /**
   * A structure to represent Outlier Correction parameter info.
   */
  typedef struct Outlier_Correct_param_t
  {
    void *image_padding; /**< pointer which point to image padding buffer */
    void *hist;          /**< pointer which point to histogram buffer */
    uint8_t SF_size;     /**< smoothing filter size*/
    uint8_t OC_max_iter; /**< maximum iteration of OC*/
    uint16_t image_padding_w;
    uint16_t image_padding_h;
  } Outlier_Correct_param;
  /**
   * A structure to represent mean filter parameter info.
   */
  typedef struct Mean_Filter_param_t
  {
    void *image_padding; /**< pointer which point to image padding buffer */
    uint8_t MF_size;     /**< mean filter size*/
    uint16_t image_padding_w;
    uint16_t image_padding_h;
  } Mean_Filter_param;
  /**
   * A structure to represent CLAHE parameter info.
   */
  typedef struct CLAHE_param_t
  {
    /**
     * @name Buffer
     */
    /*@{*/
    void *image_padding; /**< pointer which point to image padding buffer */
    void *CDF_map;       /**< pointer which point to CDF map buffer */
    /*@}*/
    /**
     * @name Parameters
     */
    /*@{*/
    uint16_t b_width;         /**< block width*/
    uint16_t b_height;        /**<block height*/
    uint8_t grid_x;           /**<grid size on x axis*/
    uint8_t grid_y;           /**<grid size on y axis*/
    uint16_t image_padding_w; /**<image padding width*/
    uint16_t image_padding_h; /**<image padding height*/
    uint16_t padding_w;       /**<padding width*/
    uint16_t padding_h;       /**<padding height*/
    float S_limit;            /**<CDF slope limit*/
    uint8_t bins;
    /*@}*/
  } CLAHE_param;

  /**
   * A structure to represent histogran equalization parameter info.
   */
  typedef struct HistEqualize_param_t
  {
    /**
     * @name Buffer
     */
    /*@{*/
    void *hist; /**< pointer which point to histogram buffer */
    void *cdf;  /**< pointer which point to CDF buffer */
    /*@}*/
    /**
     * @name Parameters
     */
    /*@{*/
    uint8_t HE_min; /**< minimum of histogram equalization */
    uint8_t HE_max; /**< minimum of histogram equalization */
    uint16_t bins;  /**< binsof histogram equalization */
    /*@}*/
  } HistEqualize_param;
  /**
   * A structure to represent image blending recovery parameter info.
   */
  typedef struct IBR_param_t
  {
    /**
     * @name Buffer
     */
    /*@{*/
    void *proc_uint8_t;
    void *proc_int16_t;
    void *result_uint8_t;
    void *sum_uint16_t;
    /*@}*/
  } IBR_param;

  typedef struct ISPParam_t
  {
    ImageInfo IMG_Info;
    IBR_param IBR_Param;
    Diff_Gaussian_param DOG_Param;
    Outlier_Correct_param OC_Param;
    Mean_Filter_param MF_Param;
    CLAHE_param CLAHE_Param;
    HistEqualize_param HE_Param;
    uint8_t *BG_IMG_8Bit;
    int16_t *IMG_substration;
  } ISPParam_st;

  void *memeryAllocate (ISPParam_st *ISPParam);
  void memeryFree (ISPParam_st *ISPParam);

#ifdef __cplusplus
}
#endif
#endif
