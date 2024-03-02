#ifndef BMP_HEADER_H_
#define BMP_HEADER_H_

#pragma pack(1)

typedef struct {
    u_int8_t     file_mark1;                  /* 'B' */
    u_int8_t     file_mark2;                  /* 'M' */
    u_int32_t    bf_size;                     /* File's size */
    u_int16_t    unused1;                     /* Aplication specific */
    u_int16_t    unused2;                     /* Aplication specific */
    u_int32_t    img_data_offset;            /* Offset to the start of image data */
} bmp_fileheader;

typedef struct {
    u_int32_t    bi_size;                     /* Size of the info header - 40 bytes */
    int32_t      width;                       /* Width of the image */
    int32_t      height;                      /* Height of the image */
    u_int16_t    planes;
    u_int16_t    bit_pix;                     /* Number of bits per pixel*/
    u_int32_t    bi_compression;              /* Type of compression */
    u_int32_t    bi_size_image;               /* Size of the image data */
    int32_t      bi_xpels_per_meter;
    int32_t      bi_ypels_per_meter;
    u_int32_t    bi_clr_used;
    u_int32_t    bi_clr_important;
} bmp_infoheader;

#pragma pack()

#endif /* BMP_HEADER_H_ */