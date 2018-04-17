// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 08/04/18
// Calculates escape steps for complex number in mandelbrot function

#include <math.h>

#include "mandelbrot.h"
#include "Bound.h"
#include "Coord.h"
//#include "LinkedList.h"
#include "BmpManager.h"

#define TRUE  1
#define FALSE 0

#define MAXIMUM_ITERATIONS 256

// Array of image data
uint8_t* image;

_Bool hasEscaped(Complex num);
int escapeSteps(Complex c);

/*
Coord mapComplexToPixel(Complex c, double pixelDistance, Bound* complexDomain, Bound* complexRange) {
    return generateCoord((int) ((c.real - complexDomain->lowerBound) / pixelDistance),
                         (int) ((c.imag - complexRange->upperBound)  / pixelDistance));
}
*/

uint8_t* generateBuddhabrot(Complex centre, int zoom) {

    // Initialising all variables needed for calculation
    double pixelDistance = pow(2, -zoom);
    double complexSize = IMAGE_SIZE * pixelDistance;

    Bound complexDomain = generateBound(centre.real - (complexSize / 2), centre.real + (complexSize / 2));
    Bound complexRange  = generateBound(centre.imag - (complexSize / 2), centre.imag + (complexSize / 2));

    image = generateImage();

    Complex iterator = generateComplex(complexDomain.lowerBound,
                                       complexRange.upperBound); // Iterates across complex plane

    while (iterator.imag > complexRange.lowerBound) {
        while (iterator.real < complexDomain.upperBound) {
            uint8_t steps = escapeSteps(iterator);

            Color pixelColor;
            if (steps == MAXIMUM_ITERATIONS) {
                pixelColor = generateColor(0, 0, 0);
            } else {
                pixelColor = generateColor(steps - 1, steps - 1, steps - 1);
            }

            drawPixel(pixelColor);

            iterator.real += (pixelDistance);
        }
        iterator.real = complexDomain.lowerBound;
        iterator.imag -= (pixelDistance);
    }

    return image;
}

void freeBuddhabrot() {
    if (image != NULL) {
        free(image);
    }
}

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
    while (!hasEscaped(z) && steps <= MAXIMUM_ITERATIONS) {
        prevZReal = z.real;
        z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
        z.imag = (prevZReal * z.imag * 2) + c.imag;

        ++steps;
    }

    return steps;
}