#include "../include/bmp_image.h"

/**
 * @brief Draws a dot at the specified coordinates with a brush size.
 * Draws a dot with the specified brush size and color
 * at the given coordinates (y1, x1) on the BMP image.
 * 
 * @param bmp The BMP image.
 * @param y1  The Y-coordinate of the dot.
 * @param x1  The X-coordinate of the dot.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t DOT(BMP *bmp, int y1, int x1) {
    // Check if BMP or image data is missing.
    if (!bmp || !bmp->img) return EXIT_FAILURE;

    // Half of the brush size.
    int half = (int)(bmp->brush_size / 2);

    // Calculate the starting and ending indices 
    // for the rows and columns to draw the dot.
    int Si = max(0, x1 - half);
    int Sj = max(0, y1 - half);
    int Ei = min(bmp->info.height, x1 + half + 1);
    int Ej = min(bmp->info.width, y1 + half + 1);

    // Iterate through the rows and columns within the brush size.
    for (int i = Si; i < Ei; i++) {
        for (int j = Sj; j < Ej; j++) {
            // Calculate the index in the image data for the current pixel.
            int ImgIdx = i * bmp->info.width * SIZE_COLOR + j * SIZE_COLOR;
            // Copy the brush color to the current pixel in the image.
            memcpy(bmp->img + ImgIdx, bmp->brush_color, SIZE_COLOR);
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Draws a line on the BMP image between two points.
 * Draws a line between the specified points (y1, x1) and (y2, x2) on the BMP image.
 * The line is drawn using the brush color and size defined in the BMP structure.
 * 
 * @param bmp The BMP image.
 * @param y1  The Y-coordinate of the starting point.
 * @param x1  The X-coordinate of the starting point.
 * @param y2  The Y-coordinate of the ending point.
 * @param x2  The X-coordinate of the ending point.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t LINE(BMP *bmp, int y1, int x1, int y2, int x2) {
    // Check if BMP, brush size, or image data is missing.
    if (!bmp || !(bmp->brush_size % 2) || !bmp->img)
        return EXIT_FAILURE;

    // If the starting and ending points are the same,
    // draw a single dot.
    if (y1 == y2 && x1 == x2) {
        DOT(bmp, y1, x1);
        return EXIT_SUCCESS;
    }

    // If the line is vertical (same X-coordinates),
    // draw the line pixel by pixel along the Y-axis.
    if (x1 == x2) {
        if (y1 > y2)
            swap(&y1, &y2, SIZE_INT);
        for (int y = y1; y <= y2; y++)
            DOT(bmp, y, x1);
        return EXIT_SUCCESS;
    }

    // If the line is horizontal (same Y-coordinates),
    // draw the line pixel by pixel along the X-axis.
    if (y1 == y2) {
        if (x1 > x2)
            swap(&x1, &x2, SIZE_INT);
        for (int x = x1; x <= x2; x++)
            DOT(bmp, y1, x);
        return EXIT_SUCCESS;
    }

    int distX, distY;
    // Calculate the absolute distances in the X and Y directions.
    if (abs(x1 - x2) <= abs(y1 - y2)) {
        // If the line is closer to vertical,
        // draw it pixel by pixel along the Y-axis.
        if (y1 > y2) {
            swap(&y1, &y2, SIZE_INT);
            swap(&x1, &x2, SIZE_INT);
        }

        distX = x2 - x1, distY = y2 - y1;

        // Calculate the corresponding X-coordinate for the current Y-coordinate.
        for (int y = y1; y <= y2; y++) {
            int x = (distX * (y - y1) + distY * x1) / distY;
            DOT(bmp, y, x);
        }
    } else {
        // If the line is closer to horizontal,
        // draw it pixel by pixel along the X-axis.
        if (x1 > x2) {
            swap(&y1, &y2, SIZE_INT);
            swap(&x1, &x2, SIZE_INT);
        }

        distX = x2 - x1, distY = y2 - y1;
        // Calculate the corresponding Y-coordinate for the current X-coordinate.
        for (int x = x1; x <= x2; x++) {
            int y = (distY * (x - x1) + distX * y1) / distX;
            DOT(bmp, y, x);
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Draws a filled rectangle on the BMP image.
 * Draws a filled rectangle with the specified dimensions and starting point
 * (y1, x1) on the BMP image. It uses the LINE function to draw the edges of the rectangle
 * and fill it with the brush color defined in the BMP structure.
 * 
 * @param bmp    The BMP image.
 * @param y1     The Y-coordinate of the top-left corner of the rectangle.
 * @param x1     The X-coordinate of the top-left corner of the rectangle.
 * @param width  The width of the rectangle.
 * @param height The height of the rectangle.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t RECTANGLE(BMP *bmp, int y1, int x1, int width, int height) {
    // Use the LINE function to draw the four sides of the rectangle.
    if (LINE(bmp, y1, x1, y1 + width, x1))  return EXIT_FAILURE;
    if (LINE(bmp, y1, x1, y1, x1 + height)) return EXIT_FAILURE;
    if (LINE(bmp, y1, x1 + height, y1 + width, x1 + height)) return EXIT_FAILURE;
    if (LINE(bmp, y1 + width, x1, y1 + width, x1 + height))  return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/**
 * @brief Draws a filled triangle on the BMP image.
 * Draws a filled triangle with the specified vertices (y1, x1), (y2, x2), and (y3, x3)
 * on the BMP image. It uses the LINE function to draw the three edges of the triangle and fill it
 * with the brush color defined in the BMP structure.
 * 
 * @param bmp The BMP image.
 * @param y1  The Y-coordinate of the first vertex of the triangle.
 * @param x1  The X-coordinate of the first vertex of the triangle.
 * @param y2  The Y-coordinate of the second vertex of the triangle.
 * @param x2  The X-coordinate of the second vertex of the triangle.
 * @param y3  The Y-coordinate of the third vertex of the triangle.
 * @param x3  The X-coordinate of the third vertex of the triangle.
 * @return EXIT_SUCCESS if successful, EXIT_FAILURE if there is an error.
 */
u_int8_t TRIANGLE(BMP *bmp, int y1, int x1, int y2, int x2, int y3, int x3) {
    // Use the LINE function to draw the three sides of the triangle.
    if (LINE(bmp, y1, x1, y3, x3)) return EXIT_FAILURE;
    if (LINE(bmp, y2, x2, y3, x3)) return EXIT_FAILURE;
    if (LINE(bmp, y1, x1, y2, x2)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
