// 
// Created by Balajanovski on 17/04/2018.
//

#include "Bound.h"

Bound generateBound(double lowerBound, double upperBound) {
    Bound newBound;
    newBound.lowerBound = lowerBound;
    newBound.upperBound = upperBound;
    return newBound;
}