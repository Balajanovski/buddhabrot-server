// 
// Created by Balajanovski on 14/04/2018.
//

#ifndef BUDDHABROT_SERVER_LINKEDLIST_H
#define BUDDHABROT_SERVER_LINKEDLIST_H

#include <stdlib.h>

#include "Complex.h"

typedef struct _Node {
    struct _Node* prev;
    struct _Node* next;

    Complex data;
} List;

List* generateList(Complex val);
void appendList(List* list, Complex val);
void prependList(List* list, Complex val);
void freeList(List* list);

#endif //BUDDHABROT_SERVER_LINKEDLIST_H
