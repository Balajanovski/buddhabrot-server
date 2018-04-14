// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 08/04/18
// Calculates escape steps for complex number in mandelbrot function

#include <math.h>

#include "mandelbrot.h"
#include "Complex.h"
#include "Bound.h"
#include "Coord.h"
#include "LinkedList.h"

#define TRUE  1
#define FALSE 0

#define MAXIMUM_ITERATIONS 256

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
   while (!hasEscaped(z) && steps < MAXIMUM_ITERATIONS) {
      prevZReal = z.real;
      z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
      z.imag = (prevZReal * z.imag * 2) + c.imag;

      ++steps;
   }

   return steps;
}

Coord mapComplexToPixel(Complex c, double pixelDistance, Bound* complexDomain, Bound* complexRange) {
    return generateCoord((int) ((c.real - complexDomain->lowerBound) / pixelDistance),
                         (int) ((c.imag - complexDomain->upperBound) / pixelDistance));
}

Color* buddhabrot(Complex centre, int zoom) {
    // Initialising all variables needed for calculation
    double pixelDistance = pow(2, -zoom);
    double complexSize = IMAGE_SIZE * pixelDistance;

    Bound complexDomain = generateBound(centre.real - complexSize, centre.real + complexSize);
    Bound complexRange  = generateBound(centre.imag - complexSize, centre.imag + complexSize);

    int pixelHistogram[IMAGE_SIZE * IMAGE_SIZE];

    Complex iterator = generateComplex(complexDomain.lowerBound,
                                       complexRange.upperBound); // Iterates across complex plane
    while (iterator.imag > nextafter(complexRange.lowerBound, INFINITY)) {
        while (iterator.real < nextafter(complexDomain.upperBound, INFINITY)) {


            iterator.real += pixelDistance;
        }
        iterator.imag -= pixelDistance;
    }
}