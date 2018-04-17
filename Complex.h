// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_COMPLEX_H
#define BUDDHABROT_SERVER_COMPLEX_H

typedef struct {
    double real;
    double imag;
} Complex;

Complex generateComplex(double real, double imag);

#endif //BUDDHABROT_SERVER_COMPLEX_H
