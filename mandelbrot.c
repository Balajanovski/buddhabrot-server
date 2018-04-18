// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 08/04/18
// Calculates escape steps for complex number in mandelbrot function

#include <math.h>
#include <stdio.h>

#include "mandelbrot.h"
#include "Bound.h"
#include "Coord.h"
//#include "LinkedList.h"
#include "BmpManager.h"
#include "Complex.h"

#define TRUE  1
#define FALSE 0

#define MAXIMUM_ITERATIONS 256

// Array of image data
uint8_t* image;

_Bool hasEscaped(Complex num);

// Calculates escape steps and then
// avoids banding
uint32_t color(Complex c);

uint8_t* generateBuddhabrot(Complex centre, int zoom) {

    // Initialising all variables needed for calculation
    double pixelDistance = pow(2, -zoom);
    double complexSize = IMAGE_SIZE * pixelDistance;

    Bound complexDomain = generateBound(centre.real - (complexSize / 2), centre.real + (complexSize / 2));
    Bound complexRange  = generateBound(centre.imag - (complexSize / 2), centre.imag + (complexSize / 2));

    image = generateImage();

    Complex iterator = generateComplex(complexDomain.lowerBound,
                                       complexRange.lowerBound); // Iterates across complex plane

    while (iterator.imag < complexRange.upperBound) {
        while (iterator.real < complexDomain.upperBound) {
            uint32_t pixelColor = color(iterator);
            drawPixel(pixelColor);

            iterator.real += (pixelDistance);
        }
        iterator.real = complexDomain.lowerBound;
        iterator.imag += (pixelDistance);
    }

    return image;
}

void freeBuddhabrot() {
    if (image != NULL) {
        free(image);
    }
}

// Linear interpolation function
unsigned int lerp(int a, int b, double factor) {
    return (a + (b-a) * factor);
}

uint32_t color(Complex c) {
    Complex z = generateComplex(c.real, c.imag);

    // Calculate steps until escape
    unsigned int steps = 1;
    double prevZReal;
    while (!hasEscaped(z) && steps <= MAXIMUM_ITERATIONS) {
        prevZReal = z.real;
        z.real = (z.real * z.real) - (z.imag * z.imag) + c.real;
        z.imag = (prevZReal * z.imag * 2) + c.imag;

        ++steps;
    }

    // Smooth iteration formula from:
    // http://iquilezles.org/www/articles/mset_smooth/mset_smooth.htm
    double sn = steps - log2(log2(z.real * z.real + z.imag * z.imag)) + 4.0;

    // Colour palette
    static const unsigned char r[] = {66,25,9 ,4 ,0  ,12 ,24, 57, 134,211,241,248,255,204,153,106};
    static const unsigned char g[] = {30,7 ,1 ,4 ,7  ,44 ,82, 125,181,236,233,201,170,128,87, 52};
    static const unsigned char b[] = {15,26,47,73,100,138,177,209,229,248,191,95, 0,  0,  0,  3};

    // linearly interpolate between iteration count values using the decimal part
    // of the smooth count
    return lerp(r[((int)(sn))%sizeof r], r[((int)(sn + 1))%sizeof r], sn-((int)(sn)))*0x10000u
           + lerp(g[((int)(sn))%sizeof r], g[((int)(sn + 1))%sizeof r], sn-((int)(sn)))*0x100u
           + lerp(b[((int)(sn))%sizeof r], b[((int)(sn + 1))%sizeof r], sn-((int)(sn)))*0x1u;


}

_Bool hasEscaped(Complex num) {
    _Bool hasEscaped = FALSE;
    if ((num.real*num.real + num.imag*num.imag) > 4) {
        hasEscaped = TRUE;
    }

    return hasEscaped;
}