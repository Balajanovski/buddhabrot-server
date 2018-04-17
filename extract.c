// James Balajan, James Balajan, z5218555
// Hornsby, Stephen Leung
// 15/04/18
// Parses URL

#include "extract.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#define INFO_START 48 // Where in the URL the info starts

void getNextField(char* message, char* buffer, int* i) {
    int j = 0;
    while (message[*i] != '/') {
        buffer[j] = message[*i];
        ++(*i); ++j;
    }
    ++(*i);
    buffer[j] = '\0';
}

triordinate extract (char *message) {
    triordinate response;
    char buffer[100];

    int i = INFO_START;

    getNextField(message, buffer, &i);
    response.z = myAtoL(buffer);

    getNextField(message, buffer, &i);
    response.x = myAtoD(buffer);

    getNextField(message, buffer, &i);
    response.y = myAtoD(buffer);

    return response;
}


double myAtoD (char* message) {
    double val, power;
    int i, sign;

    i = 0;
    sign = 1;

    if (message[i] == '-') {
        sign = -1;
        ++i;
    } else if (message[i] == '+') {
        ++i;
    }

    val = 0.0;
    while (isdigit(message[i])) {
        val = 10.0 * val + (message[i] - '0');
        ++i;
    }

    if (message[i] == '.') {
        ++i;
    }

    power = 1.0;
    while (isdigit(message[i])) {
        val = 10.0 * val + (message[i] - '0');
        power *= 10.0;
        ++i;
    }

    return sign * val / power;
}

long myAtoL (char* message) {
    return (int) myAtoD(message);
}