#include "./include/bmp_image.h"
#include "./include/api/instr.h"

/**
 * @brief Initialize a BMP object.
 * 
 * @return A pointer to the newly created BMP object, or NULL on failure.
 */
static BMP* Create_BMP(void) {
    BMP *bmp = (BMP*)malloc(sizeof(BMP));

    // Initialize other BMP object members as needed.
    if (bmp) {
        bmp->brush_color = (u_int8_t*)malloc(SIZE_BRUSH);

        if (!bmp->brush_color) {
            free(bmp);
            bmp = NULL;
        } else {
            bmp->brush_size = 1;
        }
    }

    return bmp;
}

/**
 * @brief Cleanup a BMP object.
 * 
 * @param bmp A pointer to the BMP object to be cleaned up.
 */
static void Destroy_BMP(BMP *bmp) {
    FREE_BRUSH(bmp);
    FREE_BMP(bmp);
}

int main(void) {
    // Initialize the BMP object.
    BMP *bmp = Create_BMP();

    if (!bmp) {
        fprintf(stderr, "ERROR: BMP initialization failed...\n");
        return EXIT_FAILURE;
    }

    while (strcmp(CMD, "quit")) {
        if (scanf("%s", CMD) != 1) {
            fprintf(stderr, "ERROR: invalid instruction...\n");
            Destroy_BMP(bmp);
            return EXIT_FAILURE; // Exit the loop on input failure.
        }

        // Check commands by their full name.
        if (!strcmp(CMD, "save"))
            if (Handle_Save(bmp))   fprintf(stderr, "ERROR: saving map...\n");
        if (!strcmp(CMD, "edit"))
            if (Handle_Edit(bmp))   fprintf(stderr, "ERROR: editing map...\n");
        if (!strcmp(CMD, "set"))
            if (Handle_Set(bmp))    fprintf(stderr, "ERROR: setting parameters...\n");
        if (!strcmp(CMD, "draw"))
            if (Handle_Draw(bmp))   fprintf(stderr, "ERROR: drawing...\n");
        if (!strcmp(CMD, "fill"))
            if (Handle_Fill(bmp))   fprintf(stderr, "ERROR: filling...\n");
        if (!strcmp(CMD, "insert"))
            if (Handle_Insert(bmp)) fprintf(stderr, "ERROR: inserting image...\n");
    }

    Destroy_BMP(bmp);
    return EXIT_SUCCESS;
}
