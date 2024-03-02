#include "../include/bmp_image.h"

/* ---------------------------------------SAVE--------------------------------------- */

/**
 * @brief Writes the BMP file header to the output file stream.
 * Writes the BMP file header information, including the file type marker,
 * file size, and image data offset, to the output file stream.
 * 
 * @param fout The output file stream where the header will be written.
 * @param bmp  The BMP structure containing image information.
 * @return EXIT_SUCCESS if the header is successfully written, EXIT_FAILURE otherwise.
 */
static u_int8_t _SAVE_HEADER(FILE *fout, BMP *bmp) {
    // Create a BMP file header structure.
    bmp_fileheader header;

    // Set the BMP file type markers ('BM').
    header.file_mark1 = 'B';
    header.file_mark2 = 'M';

    // Unused fields are set to zero.
    header.unused1 = 0;
    header.unused2 = 0;

    // Calculate and set the total file size including image data.
    header.bf_size = SIZE_BMP + bmp->info.width * bmp->info.height * SIZE_COLOR;
    // Set the offset to the start of image data.
    header.img_data_offset = SIZE_BMP;

    // Write the BMP file header and info to the output file stream.
    if (fwrite(&header, sizeof(header), 1, fout) != 1)
        return EXIT_FAILURE;
    if (fwrite(&bmp->info, sizeof(bmp->info), 1, fout) != 1)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * @brief Writes the image data and padding to the output file stream.
 * Writes the image data and padding to the output file stream.
 * It ensures that each row of image data is followed by the appropriate amount of padding
 * to align the data on a 4-byte boundary.
 * 
 * @param fout The output file stream where the image data will be written.
 * @param bmp  The BMP structure containing image information and data.
 * @return EXIT_SUCCESS if the image data is successfully written, EXIT_FAILURE otherwise.
 */
static u_int8_t _SAVE_INFO(FILE *fout, BMP *bmp) {
    // Calculate the padding needed for each row of the image.
    int padding = CALCULATE_PADDING(bmp->info.width);
    // Calculate the width of each row in bytes.
    int width = WIDTH(bmp->info.width);
    // Initialize the index for accessing the image data.
    int idxW = 0, byte = 0; // PADDING BYTE!

    // Loop through each row of the image.
    for (int l = 0; l < bmp->info.height; l++) {
        int line = fwrite(bmp->img + idxW, 1, width, fout);
        if (line != width) {
            return EXIT_FAILURE;
        }
        idxW += width;
        // Write the padding bytes to ensure 4-byte alignment.
        line = fwrite(&byte, 1, padding, fout);
        if (line < padding) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Saves the BMP image to a file.
 * Saves the BMP image represented by the BMP
 * structure to a file with the specified filename.
 * 
 * @param file The name of the file to save the image to.
 * @param bmp  The BMP structure containing the image data.
 * @return EXIT_SUCCESS if the image is successfully saved, EXIT_FAILURE otherwise.
 */
u_int8_t SAVE(char *file, BMP *bmp) {
    // Check for invalid input parameters.
    if (!file || !bmp || !bmp->img) 
        return EXIT_FAILURE;

    FILE *fout = fopen(file, "wb");
    if (!fout) return EXIT_FAILURE;

    // Write the BMP file header and information header.
    if (_SAVE_HEADER(fout, bmp)) {
        fclose(fout);
        return EXIT_FAILURE;
    }

    // Write the image data and padding to the output file.
    if (_SAVE_INFO(fout, bmp)) {
        fclose(fout);
        return EXIT_FAILURE;
    }

    fclose(fout);
    return EXIT_SUCCESS;
}

/* ---------------------------------------SAVE--------------------------------------- */
/* ---------------------------------------EDIT--------------------------------------- */

/**
 * @brief Reads and validates the BMP file header during image editing.
 * Reads the BMP file header from the input file stream, validates it,
 * and populates the BMP structure with the header information.
 * 
 * @param fin The input file stream.
 * @param bmp The BMP structure to store header information.
 * @return EXIT_SUCCESS if the header is successfully read and validated, EXIT_FAILURE otherwise.
 */
static u_int8_t _EDIT_HEADER(FILE *fin, BMP *bmp) {
    bmp_fileheader header;

    // Read the BMP file header from the input file stream.
    if (fread(&header, sizeof(header), 1, fin) != 1)
        return EXIT_FAILURE;
    // Validate the BMP file signature.
    if (header.file_mark1 != 'B' || header.file_mark2 != 'M')
        return EXIT_FAILURE;
    // Read and validate the BMP header.
    if (fread(&bmp->info, sizeof(bmp->info), 1, fin) != 1)
        return EXIT_FAILURE;
    // Ensure that the BMP uses 24-bit color depth (SIZE_RGB).
    if (bmp->info.bit_pix != SIZE_RGB)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/**
 * @brief Reads and populates the image data during image editing.
 * Reads and populates the image data from the input file stream,
 * taking into account padding, and stores it in the BMP structure.
 * 
 * @param fin The input file stream.
 * @param bmp The BMP structure to store the image data.
 * @return EXIT_SUCCESS if the image data is successfully read and stored, EXIT_FAILURE otherwise.
 */
static u_int8_t _EDIT_INFO(FILE *fin, BMP *bmp) {
    // Allocate memory for the image PIXEL data.
    int rgb_size = bmp->info.width * bmp->info.height * SIZE_COLOR;
    bmp->img = malloc(rgb_size);
    if (!bmp->img) return EXIT_FAILURE;

    // Calculate the padding needed for each row of the image.
    int padding = CALCULATE_PADDING(bmp->info.width);
    // Calculate the width of each row in bytes.
    int width = WIDTH(bmp->info.width);
    // Initialize the index for accessing the image data.
    int idxW = 0;

    // Loop through each row of the image.
    for (int l = 0; l < bmp->info.height; l++) {
        // Read a line of image data from the input file stream.
        int line = fread(bmp->img + idxW, 1, width, fin);
        // If reading the line fails, free the memory.
        if (line != width) {
            FREE_BMP(bmp);
            return EXIT_FAILURE;
        }
        idxW += width;
        // Skip padding bytes.
        fseek(fin, padding, SEEK_CUR);
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Edits a BMP image by reading and updating its content from an input file.
 * Reads an input BMP file, validates and stores its contents in the
 * provided BMP structure, effectively editing the image.
 * 
 * @param file The filename of the input BMP file.
 * @param bmp  The BMP structure to store the edited image.
 */
u_int8_t EDIT(char *file, BMP *bmp) {
    // Check for invalid input parameters.
    if (!bmp || !file)
        return EXIT_FAILURE;

    FILE *fin = fopen(file, "rb");
    if (!fin) return EXIT_FAILURE;

    // Edit the BMP file header and information header.
    if (_EDIT_HEADER(fin, bmp)) {
        fclose(fin);
        return EXIT_FAILURE;
    }

    // Edit the image data and padding to the output file.
    if (_EDIT_INFO(fin, bmp)) {
        fclose(fin);
        return EXIT_FAILURE;
    }

    fclose(fin);
    return EXIT_SUCCESS;
}

/* ---------------------------------------EDIT--------------------------------------- */
/* --------------------------------------INSERT-------------------------------------- */

/**
 * @brief Reads and validates the BMP file header and information header from a file.
 * Reads and validates both the BMP file header and information header
 * from the input file stream. It checks if the file signature and color depth are valid.
 * 
 * @param fin    The input file stream.
 * @param header Pointer to a bmp_fileheader structure to store the file header.
 * @param info   Pointer to a bmp_infoheader structure to store the information header.
 * @return EXIT_SUCCESS if the headers are successfully read and validated, EXIT_FAILURE otherwise.
 */
static u_int8_t _HEADER_INFO(FILE *fin, bmp_fileheader *header, bmp_infoheader *info) {
    // Read and validate the BMP header.
    if (fread(header, sizeof(*header), 1, fin) != 1)
        return EXIT_FAILURE;
    // Validate the BMP file signature.
    if (header->file_mark1 != 'B' || header->file_mark2 != 'M')
        return EXIT_FAILURE;
    // Read and validate the BMP info.
    if (fread(info, sizeof(*info), 1, fin) != 1)
        return EXIT_FAILURE;
    // Validate the BMP information header.
    if (info->bit_pix != SIZE_RGB)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

/**
 * @brief Reads image data and padding from a file and stores it in a buffer.
 * Reads image data and padding from the input file stream and stores
 * it in the provided image buffer. It correctly accounts for padding bytes in each row.
 * 
 * @param fin     The input file stream.
 * @param img     Pointer to the image data buffer where the data will be stored.
 * @param _width  The width of the image.
 * @param _height The height of the image.
 * @return EXIT_SUCCESS if the image data is successfully read and stored, EXIT_FAILURE otherwise.
 */
static u_int8_t _READ_INFO(FILE *fin, char *img, int _width, int _height) {
    // Calculate the padding needed for each row of the image.
    int padding = CALCULATE_PADDING(_width);
    // Calculate the width of each row in bytes.
    int width = WIDTH(_width);
    // Initialize the index for accessing the image data.
    int idxW = 0;

    // Loop through each row of the image.
    for (int l = 0; l < _height; l++) {
        // Read a line of image data from the input file stream.
        int line = fread(img + idxW, 1, width, fin);
        // If reading the line fails, free the memory.
        if (line != width) {
            return EXIT_FAILURE;
        }
        idxW += width;
        // Skip padding bytes.
        fseek(fin, padding, SEEK_CUR);
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Copies image data from one buffer to another with specified offsets and dimensions.
 * Copies image data from one buffer to another, considering specified offsets
 * and dimensions. It is used to insert one image into another at a given position.
 * 
 * @param bmp     The target BMP structure where the image data will be copied.
 * @param img     The source image data buffer to be copied, RGB pixels info.
 * @param y       The vertical position (row) where the insertion will start.
 * @param x       The horizontal position (column) where the insertion will start.
 * @param _width  The width of the source image to be copied.
 * @param _height The height of the source image to be copied.
 * @return EXIT_SUCCESS if the image data is successfully copied, EXIT_FAILURE otherwise.
 */
static u_int8_t _COPY_INFO(BMP *bmp, char *img, int y, int x, int _width, int _height) {
    int height = bmp->info.height;
    int width  = bmp->info.width;

    // Calculate the source and target indices.
    int idxH = height * y * SIZE_COLOR;
    int idxW = width  * x * SIZE_COLOR;

    // If both y and x are greater than 0,
    // adjust the indices accordingly.
    if (y > 0 && x > 0) {
        idxW = (y + x * width) * SIZE_COLOR;
        idxH = 0;
    }

    // Calculate the width (W) and height (H) for copying.
    int W = (_width  + y) > width  ? (width - y) * SIZE_COLOR : _width * SIZE_COLOR;
    int H = (_height + x) > height ? (height - x) : _height;

    for (int l = 0; l < H; l++) {
        memcpy(bmp->img + idxW, img + idxH, W);
        idxH += W, idxW += W;

        // Adjust indices for the next row if necessary.
        if ((y + _width) >= width) {
            idxW += (y * SIZE_COLOR);
            idxH += (_width - width + y) * SIZE_COLOR;
        } else {
            idxW += SIZE_COLOR * (width - _width);
        }
    }

    return EXIT_SUCCESS;
}

/**
 * @brief Inserts an image into a BMP structure at a specified position.
 * Inserts an image from a file into a BMP structure at a specified position.
 * It reads the image data from the file, copies it into the BMP structure, and adjusts the
 * target position accordingly.
 * 
 * @param file The filename of the image file to insert.
 * @param bmp  The target BMP structure where the image will be inserted.
 * @param y    The vertical position (row) where the insertion will start.
 * @param x    The horizontal position (column) where the insertion will start.
 * @return EXIT_SUCCESS if the image is successfully inserted, EXIT_FAILURE otherwise.
 */
u_int8_t INSERT(char *file, BMP *bmp, int y, int x) {
    if (!file || !bmp || !bmp->img) 
        return EXIT_FAILURE;

    FILE *fin = fopen(file, "rb");
    if (!fin) return EXIT_FAILURE;

    bmp_fileheader header;
    bmp_infoheader info;

    // Read and validate the BMP header and information header.
    if (_HEADER_INFO(fin, &header, &info)) {
        fclose(fin);
        return EXIT_FAILURE;
    }

    int rgb_size = info.width * info.height * SIZE_COLOR;
    char *img = (char*)malloc(rgb_size);

    if (!img) {
        fclose(fin);
        return EXIT_FAILURE;
    }

    // Read image data from the file.
    if (_READ_INFO(fin, img, info.width, info.height)) {
        free(img);
        fclose(fin);
        return EXIT_FAILURE;
    }

    // Copy the image data into the BMP structure at the specified position.
    if (_COPY_INFO(bmp, img, y, x, info.width, info.height)) {
        free(img);
        fclose(fin);
        return EXIT_FAILURE;
    }

    free(img);
    fclose(fin);
    return EXIT_SUCCESS;
}

/* --------------------------------------INSERT-------------------------------------- */
