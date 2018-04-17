// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_BOUND_H
#define BUDDHABROT_SERVER_BOUND_H

typedef struct {
    double lowerBound;
    double upperBound;
} Bound;

Bound generateBound(double lowerBound, double upperBound);

#endif //BUDDHABROT_SERVER_BOUND_H
