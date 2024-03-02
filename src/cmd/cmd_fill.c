#include "../include/bmp_image.h"

/**
 * @brief Sets the brush color in the BMP image.
 * Sets the brush color to the specified RGB values (R, G, B) in the BMP image.
 *
 * @param bmp The BMP image.
 * @param R   The red component of the brush color.
 * @param G   The green component of the brush color.
 * @param B   The blue component of the brush color.
 * @return EXIT_SUCCESS if successful, or EXIT_FAILURE if there is an error.
 */
u_int8_t SET_COLOR(BMP *bmp, u_int8_t R, u_int8_t G, u_int8_t B) {
    if (!bmp || !bmp->brush_color)
        return EXIT_FAILURE;

    memcpy(bmp->brush_color + 2, &R, 1);
    memcpy(bmp->brush_color + 1, &G, 1);
    memcpy(bmp->brush_color + 0, &B, 1);

    return EXIT_SUCCESS;
}

/**
 * @brief Sets the brush size in the BMP image.
 * Sets the brush size to the specified value in the BMP image.
 * 
 * @param bmp        The BMP image.
 * @param brush_size The brush size to set.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t SET_LINE(BMP *bmp, u_int8_t brush_size) {
    if (!(brush_size & 1) || !bmp) return EXIT_FAILURE;
    bmp->brush_size = brush_size;
    return EXIT_SUCCESS;
}

/**
 * @brief Recursively fills a pixel and its neighboring pixels with the brush color.
 * Used by the FILL function to recursively fill a pixel and
 * its neighboring pixels with the brush color. It stops when it encounters a different
 * color or reaches the image boundaries, DFS fill algorithm.
 * 
 * @param bmp   The BMP image.
 * @param brush The color to fill with.
 * @param y     The Y-coordinate of the pixel.
 * @param x     The X-coordinate of the pixel.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t _FILL_PIXEL(BMP *bmp, u_int8_t *brush, int y, int x) {
    if (y < 0 || y >= bmp->info.width || x < 0 || x >= bmp->info.height)
        return EXIT_FAILURE;

    int pixel = (y + x * bmp->info.width) * SIZE_COLOR;

    if (bmp->img[pixel] != brush[0] || 
        bmp->img[pixel + 1] != brush[1] ||
        bmp->img[pixel + 2] != brush[2])
        return EXIT_FAILURE;

    if (bmp->img[pixel] == bmp->brush_color[0] &&
        bmp->img[pixel + 1] == bmp->brush_color[1] &&
        bmp->img[pixel + 2] == bmp->brush_color[2])
        return EXIT_FAILURE;

    memcpy(bmp->img + pixel, bmp->brush_color, SIZE_COLOR);

    _FILL_PIXEL(bmp, brush, y + 1, x);
    _FILL_PIXEL(bmp, brush, y, x + 1);
    _FILL_PIXEL(bmp, brush, y - 1, x);
    _FILL_PIXEL(bmp, brush, y, x - 1);

    return EXIT_SUCCESS;
}

/**
 * @brief Fills an area of the BMP image with the brush color.
 * Fills an area of the BMP image starting from the specified pixel (y, x)
 * with the brush color. It uses a recursive algorithm to fill the connected region.
 *
 * @param bmp The BMP image.
 * @param y   The Y-coordinate of the starting pixel.
 * @param x   The X-coordinate of the starting pixel.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t FILL(BMP *bmp, int y, int x) {
    if (!bmp || !bmp->img) 
        return EXIT_FAILURE;

    u_int8_t *brush = (u_int8_t*)malloc(SIZE_COLOR);
    if (!brush) return EXIT_FAILURE;

    int pixel = (y + x * bmp->info.width) * SIZE_COLOR;

    memcpy(brush, bmp->img + pixel, SIZE_COLOR);

    if (brush[0] == bmp->brush_color[0] &&
        brush[1] == bmp->brush_color[1] &&
        brush[2] == bmp->brush_color[2]) {
        free(brush);
        return EXIT_FAILURE;
    }

    _FILL_PIXEL(bmp, brush, y, x);

    free(brush);
    brush = NULL;
    return EXIT_SUCCESS;
}
