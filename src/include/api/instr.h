#ifndef INSTR_H_
#define INSTR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../bmp_image.h"
#include "../lib/cmd_draw.h"
#include "../lib/cmd_fill.h"
#include "../lib/cmd_insert.h"

#define INSTR_LENGTH 101

// Buffer to store command strings.
static char CMD[INSTR_LENGTH];

// Handles the "save" command to save the BMP image to a file.
u_int8_t     Handle_Save     (BMP *bmp);
// Handles the "edit" command to edit the BMP image from a file.
u_int8_t     Handle_Edit     (BMP *bmp);
// Handles the "set" command to set various properties of the BMP image.
u_int8_t     Handle_Set      (BMP *bmp);
// Handles the "draw" command to draw shapes on the BMP image.
u_int8_t     Handle_Draw     (BMP *bmp);
// Handles the "fill" command to fill an area of the BMP image with the current brush color.
u_int8_t     Handle_Fill     (BMP *bmp);
// Handles the "insert" command to insert an image from a file into the BMP image.
u_int8_t     Handle_Insert   (BMP *bmp);

#endif /* INSTR_H_ */
