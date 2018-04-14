// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 08/04/18
// Calculates escape steps for complex number in mandelbrot function

#include <math.h>

#define TRUE  1
#define FALSE 0

_Bool hasEscaped(double x, double y) {
   _Bool hasEscaped = FALSE;
   if ((x*x + y*y) > 4) {
      hasEscaped = TRUE;
   }

   return hasEscaped;
}

int escapeSteps(double x, double y) {
   int steps = 1;
   double zX, zY;
   zX = x;
   zY = y;   
   
   double prevZX;
   while (!hasEscaped(zX, zY) && steps < 256) {
      prevZX = zX;
      zX = (zX * zX) - (zY * zY) + x;
      zY = (prevZX * zY * 2) + y;

      ++steps;
   }

   return steps;
}
