#ifndef FILL_H_
#define FILL_H_

#include "../bmp_image.h"

// Sets the brush color in the BMP image.
u_int8_t                 SET_COLOR          (BMP *bmp, u_int8_t R, u_int8_t G, u_int8_t B);
// Sets the brush size in the BMP image.
u_int8_t                 SET_LINE           (BMP *bmp, u_int8_t brush_size);
// Fills an area of the BMP image with the brush color.
u_int8_t                 FILL               (BMP *bmp, int y, int x);

#endif /* FILL_H_ */
