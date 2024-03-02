#ifndef BMP_H_
#define BMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./bmp_header.h"

#define SIZE_INT      4     // SIZE INTEGER

#define SIZE_BRUSH    3     // RGB
#define SIZE_BMP      54    // SIZE BMP META DATA STRUCTURE

#define SIZE_COLOR    3     // SIZE BYTES RGB PIXEL
#define SIZE_RGB      3 * 8 // SIZE BITS RGB PIXEL

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define swap(a, b, size) do { \
    char *temp = (char*)malloc(size); \
    if (!temp) exit(EXIT_FAILURE); \
    memcpy(temp, a, size); \
    memcpy(a, b, size); \
    memcpy(b, temp, size); \
    free(temp); \
} while (0)

#define FREE_MEMORY(ptr) do { \
    if (*(ptr)) { \
        free(*(ptr)); \
        *(ptr) = NULL; \
    } \
} while (0)

#define FREE_BMP(bmp)   FREE_MEMORY((void**)&(bmp)->img)
#define FREE_BRUSH(bmp) FREE_MEMORY((void**)&(bmp)->brush_color)

#define WIDTH(width) (width * SIZE_COLOR)
#define CALCULATE_PADDING(width) (((4 - ((3 * (width)) % 4)) % 4))

typedef struct BitMapPicture {
    bmp_infoheader   info;            // BMP information header.
    u_int8_t         *img;            // BMP vector of pixels.
    u_int8_t         brush_size;      // BMP brush size.
    u_int8_t         *brush_color;    // BMP brush color.
} BMP;

#endif /* BMP_H_ */
