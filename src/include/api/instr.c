#include "./instr.h"

/**
 * @brief Handles the "save" command to save the BMP image to a file.
 * 
 * @param bmp The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the image is successfully saved, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Save(BMP *bmp) {
    if (fscanf(stdin, "%s", CMD) != 1)
        return EXIT_FAILURE;
    return SAVE(CMD, bmp);
}

/**
 * @brief Handles the "edit" command to edit the BMP image from a file.
 * 
 * @param bmp The BMP structure to store the edited image.
 * @return EXIT_SUCCESS if the image is successfully edited, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Edit(BMP *bmp) {
    if (fscanf(stdin, "%s", CMD) != 1)
        return EXIT_FAILURE;
    EDIT(CMD, bmp);
    if (!bmp->img)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/**
 * @brief Handles the "set" command to set various properties of the BMP image.
 * 
 * @param bmp The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the properties are successfully set, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Set(BMP *bmp) {
    int witdth = 0;
    u_int8_t R = 0, G = 0, B = 0;
    
    if (fscanf(stdin, "%s", CMD) != 1)
        return EXIT_FAILURE;

    switch (CMD[0]) {
        case 'd':
            if (fscanf(stdin, "%hhu%hhu%hhu", &R, &G, &B) != 3)
                return EXIT_FAILURE;
            if (SET_COLOR(bmp, R, G, B))
                return EXIT_FAILURE;
            break;

        case 'l':
            if (fscanf(stdin, "%d", &witdth) != 1)
                return EXIT_FAILURE;
            if (SET_LINE(bmp, witdth))
                return EXIT_FAILURE;
            break;

        default:
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Handles the "draw" command to draw shapes on the BMP image.
 * 
 * @param bmp The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the shapes are successfully drawn, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Draw(BMP *bmp) {
    int y1 = 0, x1 = 0;
    int y2 = 0, x2 = 0;
    int y3 = 0, x3 = 0;
    int width = 0, height = 0;

    if (fscanf(stdin, "%s", CMD) != 1)
        return EXIT_FAILURE;

    switch (CMD[0]) {
        case 'l':
            if (fscanf(stdin, "%d%d%d%d", &y1, &x1, &y2, &x2) != 4)
                return EXIT_FAILURE;
            if (LINE(bmp, y1, x1, y2, x2))
                return EXIT_FAILURE;
            break;

        case 'r':
            if (fscanf(stdin, "%d%d%d%d", &y1, &x1, &width, &height) != 4)
                return EXIT_FAILURE;
            if (RECTANGLE(bmp, y1, x1, width, height))
                return EXIT_FAILURE;
            break;

        case 't':
            if (fscanf(stdin, "%d%d%d%d%d%d", &y1, &x1, &y2, &x2, &y3, &x3) != 6)
                return EXIT_FAILURE;
            if (TRIANGLE(bmp, y1, x1, y2, x2, y3, x3))
                return EXIT_FAILURE;
            break;

        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Handles the "fill" command to fill an area of the BMP image with the current brush color.
 * 
 * @param bmp The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the area is successfully filled, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Fill(BMP *bmp) {
    int y = 0, x = 0;
    if (fscanf(stdin, "%d%d", &y, &x) != 2)
        return EXIT_FAILURE;
    FILL(bmp, y, x);
    return EXIT_SUCCESS;
}

/**
 * @brief Handles the "insert" command to insert an image from a file into the BMP image.
 * 
 * @param bmp The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the image is successfully inserted, EXIT_FAILURE otherwise.
 */
u_int8_t Handle_Insert(BMP *bmp) {
    int y = 0, x = 0;
    if (fscanf(stdin, "%s", CMD) != 1)
        return EXIT_FAILURE;
    if (fscanf(stdin, "%d%d", &y, &x) != 2)
        return EXIT_FAILURE;
    if (INSERT(CMD, bmp, y, x))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
