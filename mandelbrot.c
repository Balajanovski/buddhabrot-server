// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 08/04/18
// Calculates escape steps for complex number in mandelbrot function

#include <math.h>
#include <stdint.h>

#include "mandelbrot.h"
#include "Complex.h"
#include "Bound.h"

#define TRUE  1
#define FALSE 0

#define MAXIMUM_ITERATIONS 50

#define IMAGE_SIZE 511



_Bool hasEscaped(Complex num) {
   _Bool hasEscaped = FALSE;
   if ((num.real*num.real + num.imag*num.imag) > 4) {
      hasEscaped = TRUE;
   }

   return hasEscaped;
}

int escapeSteps(Complex c) {
   int steps = 1;

   Complex z = generateComplex(c.real, c.imag);

   double prevZReal;
   while (!hasEscaped(z) && steps < 256) {
      prevZReal = z.real;
      z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
      z.imag = (prevZReal * z.imag * 2) + c.imag;

      ++steps;
   }

   return steps;
}

void buddhabrot(Complex centre, int zoom) {

    // Initialising all variables needed for calculation
    double pixelDistance = pow(2, -zoom);
    double complexSize = IMAGE_SIZE * pixelDistance;

    Bound complexDomain = generateBound(centre.real - complexSize, centre.real + complexSize);
    Bound complexRange  = generateBound(centre.imag - complexSize, centre.imag + complexSize);

    int pixelHistogram[IMAGE_SIZE * IMAGE_SIZE];

}