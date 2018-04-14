// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_MANDELBROT_H_H
#define BUDDHABROT_SERVER_MANDELBROT_H_H

#include "Complex.h"

_Bool hasEscaped(Complex num);
int escapeSteps(Complex c);
void buddhabrot(Complex centre, int zoom);

#endif //BUDDHABROT_SERVER_MANDELBROT_H_H
