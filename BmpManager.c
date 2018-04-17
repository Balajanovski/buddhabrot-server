// 
// Created by Balajanovski on 16/04/2018.
//

#include "BmpManager.h"

#include <assert.h>
#include <stdint.h>

#define BITS_IN_BYTE 8
#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;

// Private variable representing the image data
// According to the BMP specification
uint8_t* image;

// Utility function which behaves like fwrite
// Except it works on arrays
void arrayWrite(unsigned int data, size_t size, uint8_t* stream);

// The place in the image array where writing to
// This is used by arrayWrite
unsigned int imagePos;

uint8_t* generateImage() {
    // Initialization
    uint32_t fileSize = OFFSET + (IMAGE_SIZE * IMAGE_SIZE * BYTES_PER_PIXEL);
    image = (uint8_t*) malloc(fileSize); // Allocate the image
    imagePos = 0;                        // Reset imagePos

    // From here on the code uses arrayWrite
    // to write the BMP header
    bits16 magicNumber = MAGIC_NUMBER;
    arrayWrite (magicNumber, sizeof magicNumber, image);

    arrayWrite (fileSize, sizeof fileSize, image);

    bits32 reserved = 0;
    arrayWrite (reserved, sizeof reserved, image);

    bits32 offset = OFFSET;
    arrayWrite (offset, sizeof offset, image);

    bits32 dibHeaderSize = DIB_HEADER_SIZE;
    arrayWrite (dibHeaderSize, sizeof dibHeaderSize, image);

    bits32 width = IMAGE_SIZE;
    arrayWrite (width, sizeof width, image);

    bits32 height = IMAGE_SIZE;
    arrayWrite (height, sizeof height, image);

    bits16 planes = NUMBER_PLANES;
    arrayWrite (planes, sizeof planes, image);

    bits16 bitsPerPixel = BITS_PER_PIXEL;
    arrayWrite (bitsPerPixel, sizeof bitsPerPixel, image);

    bits32 compression = NO_COMPRESSION;
    arrayWrite (compression, sizeof compression, image);

    bits32 imageSize = (IMAGE_SIZE * IMAGE_SIZE * BYTES_PER_PIXEL);
    arrayWrite (imageSize, sizeof imageSize, image);

    bits32 hResolution = PIX_PER_METRE;
    arrayWrite (hResolution, sizeof hResolution, image);

    bits32 vResolution = PIX_PER_METRE;
    arrayWrite (vResolution, sizeof vResolution, image);

    bits32 numColors = NUM_COLORS;
    arrayWrite (numColors, sizeof numColors, image);

    bits32 importantColors = NUM_COLORS;
    arrayWrite (importantColors, sizeof importantColors, image);

    return image;
}

void drawPixel(Color pixel) {
    unsigned int pixelInteger = 0;
    pixelInteger |= pixel.r;
    pixelInteger |= (pixel.g << BITS_IN_BYTE);
    pixelInteger |= (pixel.b << (2 * BITS_IN_BYTE));

    arrayWrite(pixelInteger, BYTES_PER_PIXEL, image);
}

void freeImage() {
    if (image != NULL) {
        free(image);
    }
}

void arrayWrite(unsigned int data, size_t size, uint8_t* stream) {
    int i = 0;
    while (i < size) {
        int meme = (data >> (i * BITS_IN_BYTE)) & 0xFF;
        stream[imagePos] = (data >> (i * BITS_IN_BYTE)) & 0xFF;

        ++i; ++imagePos;
    }
}