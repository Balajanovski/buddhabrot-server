// 
// Created by Balajanovski on 16/04/2018.
//

#ifndef BUDDHABROT_SERVER_BMPMANAGER_H
#define BUDDHABROT_SERVER_BMPMANAGER_H

#include <stdlib.h>

#define IMAGE_SIZE 512

// Generates a blank image array which hasn't
// Been written to
//
// Returns pointer to image array
uint8_t* generateImage();

// Draws pixel to image array
void drawPixel(uint32_t pixel);

// Frees image array
void freeImage();

#endif //BUDDHABROT_SERVER_BMPMANAGER_H
