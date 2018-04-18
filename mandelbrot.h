// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_MANDELBROT_H_H
#define BUDDHABROT_SERVER_MANDELBROT_H_H

#include "Complex.h"
#include "Color.h"

uint8_t* generateMandelbrot(Complex centre, int zoom);
void freeMandelbrot();

#endif //BUDDHABROT_SERVER_MANDELBROT_H_H
