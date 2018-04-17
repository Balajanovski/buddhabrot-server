// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_COLOR_H
#define BUDDHABROT_SERVER_COLOR_H

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

Color generateColor(uint8_t r, uint8_t g, uint8_t b);

#endif //BUDDHABROT_SERVER_COLOR_H
