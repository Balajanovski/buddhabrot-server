// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_MANDELBROT_H_H
#define BUDDHABROT_SERVER_MANDELBROT_H_H

#include "Complex.h"
#include "Color.h"

uint8_t* generateBuddhabrot(Complex centre, int zoom);
void freeBuddhabrot();

#endif //BUDDHABROT_SERVER_MANDELBROT_H_H
