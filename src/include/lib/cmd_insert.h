#ifndef INSERT_H_
#define INSERT_H_

#include "../bmp_image.h"

// Saves the BMP image to a file.
u_int8_t              SAVE               (char *file, BMP *bmp);
// Edits a BMP image by reading and updating its content from an input file.
u_int8_t              EDIT               (char *file, BMP *bmp);
// Inserts an image into a BMP structure at a specified position.
u_int8_t              INSERT             (char *file, BMP *bmp, int y, int x);

#endif /* INSERT_H_ */