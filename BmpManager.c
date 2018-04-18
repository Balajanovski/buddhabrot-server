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
    uint16_t magicNumber = MAGIC_NUMBER;
    arrayWrite (magicNumber, sizeof magicNumber, image);

    arrayWrite (fileSize, sizeof fileSize, image);

    uint32_t reserved = 0;
    arrayWrite (reserved, sizeof reserved, image);

    uint32_t offset = OFFSET;
    arrayWrite (offset, sizeof offset, image);

    uint32_t dibHeaderSize = DIB_HEADER_SIZE;
    arrayWrite (dibHeaderSize, sizeof dibHeaderSize, image);

    uint32_t width = IMAGE_SIZE;
    arrayWrite (width, sizeof width, image);

    uint32_t height = IMAGE_SIZE;
    arrayWrite (height, sizeof height, image);

    uint16_t planes = NUMBER_PLANES;
    arrayWrite (planes, sizeof planes, image);

    uint16_t bitsPerPixel = BITS_PER_PIXEL;
    arrayWrite (bitsPerPixel, sizeof bitsPerPixel, image);

    uint32_t compression = NO_COMPRESSION;
    arrayWrite (compression, sizeof compression, image);

    uint32_t imageSize = (IMAGE_SIZE * IMAGE_SIZE * BYTES_PER_PIXEL);
    arrayWrite (imageSize, sizeof imageSize, image);

    uint32_t hResolution = PIX_PER_METRE;
    arrayWrite (hResolution, sizeof hResolution, image);

    uint32_t vResolution = PIX_PER_METRE;
    arrayWrite (vResolution, sizeof vResolution, image);

    uint32_t numColors = NUM_COLORS;
    arrayWrite (numColors, sizeof numColors, image);

    uint32_t importantColors = NUM_COLORS;
    arrayWrite (importantColors, sizeof importantColors, image);

    return image;
}

void drawPixel(uint32_t pixel) {
    arrayWrite(pixel, BYTES_PER_PIXEL, image);
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