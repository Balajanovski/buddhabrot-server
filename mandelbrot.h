// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_MANDELBROT_H_H
#define BUDDHABROT_SERVER_MANDELBROT_H_H

#include "Complex.h"
#include "Color.h"

_Bool hasEscaped(Complex num);
int escapeSteps(Complex c);
Color* buddhabrot(Complex centre, int zoom);

#endif //BUDDHABROT_SERVER_MANDELBROT_H_H
