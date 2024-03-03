# BMP Image Library

This library provides functionalities for manipulating BMP images. It allows for **basic image operations** such as: *saving and editing images, inserting one image into another, setting brush properties, and drawing shapes including dots, lines, rectangles, and triangles*.

## BMP Image Structure

The BMP image format is characterized by its simplicity and comprises mainly two parts: a **file header and an info header**, followed by the actual **pixel data** (**bitmap**).

**File Header (`bmp_fileheader`)**

- **Signature**: `2` bytes (`'B'` and `'M'` in ASCII) indicating the BMP file format.
- **File Size**: `4` bytes representing the **total size** of the file.
- **Reserved**: `4` bytes (**2 fields** of `2` bytes each) unused and application-specific.
- **Image Data Offset**: `4` bytes specifying the **offset** to the start of the image data (**pixel matrix**).

**Info Header (`bmp_infoheader`)**

- **Size**: `4` bytes indicating the **size of the info header**, fixed at **40** bytes.
- **Width**: `4` bytes for the width of the image (**number of columns**).
- **Height**: `4` bytes for the height of the image (**number of rows**).
- **Planes**: `2` bytes set to the fixed value of `1`.
- **Bit Count**: `2` bytes for the **number of bits per pixel**, always set to `24` in this project, meaning each pixel is represented by `3` bytes (**RGB channels**).
- **Compression**: `4` bytes for the **type of compression**, which will be `0` (**no compression**).
- **Image Size**: `4` bytes referring to the **size of the pixel matrix**, including ***any added padding***.
- **X Pixels Per Meter**: `4` bytes for the **horizontal** print resolution, set to `0` for simplification.
- **Y Pixels Per Meter**: `4` bytes for the **vertical** print resolution, also set to `0`.
- **Colors Used**: `4` bytes for the **number of colors** in the color palette, set to `0` (**not used in this project**).
- **Colors Important**: `4` bytes for the **number of important colors**, set to `0`, implying **all colors are important**.

## Pixel Matrix

The pixel data is stored in a matrix of `height x width`, but **may include padding** at the end of each row to ensure that each line starts at a `4`-byte boundary. This padding should be ignored during reading and explicitly set to `0` during writing.
**Note:** the *pixel data is stored in reverse order*, with the first row of the matrix actually representing the bottom line of the image. The color channels for each pixel are in **BGR (Blue, Green, Red)** order.

## Image Manipulation

- `SAVE (char *file, BMP *bmp)`: Saves the modified BMP image to a file.
- `EDIT (char *file, BMP *bmp)`: Loads a BMP image from a file, allowing it to be edited or manipulated.
- `INSERT (char *file, BMP *bmp, int y, int x)`: Inserts another BMP image into the current BMP structure at the specified position.
- `FILL (BMP *bmp, int y, int x)`: Fills an area of the BMP image with the current brush color, starting from the specified coordinates.
- `SET_COLOR (BMP *bmp, u_int8_t R, u_int8_t G, u_int8_t B)`: Sets the brush color in the BMP image for subsequent drawing or filling operations.
- `SET_LINE (BMP *bmp, u_int8_t brush_size)`: Sets the brush size for drawing operations on the BMP image.

## Shape Drawing

- `DOT (BMP *bmp, int y1, int x1)`: Draws a dot at the specified coordinates on the BMP image, using the currently set brush size and color.
- `LINE (BMP *bmp, int y1, int x1, int y2, int x2)`: Draws a line between two points on the BMP image, using the currently set brush size and color.
- `RECTANGLE (BMP *bmp, int y1, int x1, int width, int height)`: Purpose: Draws a filled rectangle on the BMP image, using the currently set brush color.
- `TRIANGLE (BMP *bmp, int y1, int x1, int y2, int x2, int y3, int x3)`: Draws a filled triangle on the BMP image, connecting three specified points with the currently set brush color.

## Build the Project

1. Navigate to the `build` directory.
2. Run the `make` command to build the executable.

The `Makefile` provided will compile the source files and link them with the necessary libraries.

```bash
    cd ./build
    make
```

## Run the Project

After building the project, you can run the program with the shell script `temple_run.sh` to execute the program. This script sets up the necessary environment and arguments for the program to run the test suite.

```bash
    ./bmp_run.sh
    ............................Basic Commands.........................
    Test 0.......................................................passed
    Test valgrind................................................passed
    
    ............................Insert Image...........................
    Test 0.......................................................passed
    Test valgrind................................................passed
    Test 1.......................................................passed
    Test valgrind................................................passed
    Test 2.......................................................passed
    Test valgrind................................................passed
    Test 3.......................................................passed
    Test valgrind................................................passed
    Test 4.......................................................passed
    Test valgrind................................................passed

    ............................Draw Commands..........................
    Test 0.......................................................passed
    Test valgrind................................................passed
    Test 1.......................................................passed
    Test valgrind................................................passed
    Test 2.......................................................passed
    Test valgrind................................................passed
    Test 3.......................................................passed
    Test valgrind................................................passed
    
    ............................Fill Color.............................
    Test 0.......................................................passed
    Test valgrind................................................passed
    Test 1.......................................................passed
    Test valgrind................................................passed
    Test 2.......................................................passed
    Test valgrind................................................passed
    
    ............................Mix Commands...........................
    Test 0.......................................................passed
    Test valgrind................................................passed
    Test 1.......................................................passed
    Test valgrind................................................passed
    Test 2.......................................................passed
    Test valgrind................................................passed
    Test 3.......................................................passed
    Test valgrind................................................passed
    Test 4.......................................................passed
    Test valgrind................................................passed

```
