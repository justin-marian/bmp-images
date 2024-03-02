#ifndef DRAW_H_
#define DRAW_H_

#include "../bmp_image.h"

// Draws a dot at the specified coordinates with a brush size.
u_int8_t                 DOT                (BMP *bmp, int y1, int x1);
// Draws a line on the BMP image between two points.
u_int8_t                 LINE               (BMP *bmp, int y1, int x1, int y2, int x2);
// Draws a filled rectangle on the BMP image.
u_int8_t                 RECTANGLE          (BMP *bmp, int y1, int x1, int width, int height);
// Draws a filled triangle on the BMP image.
u_int8_t                 TRIANGLE           (BMP *bmp, int y1, int x1, int y2, int x2, int y3, int x3);

#endif /* DRAW_H_ */