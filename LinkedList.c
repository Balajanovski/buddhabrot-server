// 
// Created by Balajanovski on 14/04/2018.
//

#include "LinkedList.h"

List* generateList(Complex val) {
    List* newList = malloc(sizeof(List));
    newList->next = newList->prev = NULL;
    newList->data = val;

    return newList;
}

List* appendList(List* list, Complex val) {
    // Create the new node
    struct _Node* newNode = malloc(sizeof(struct _Node));
    newNode->next = NULL;
    newNode->data = val;

    // Find the last node
    struct _Node* lastNode = list;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    // Link the new node into the list
    lastNode->next = newNode;
    newNode->prev = lastNode;
}

List* prependList(List* list, Complex val) {
    // Create the new node
    struct _Node* newNode = malloc(sizeof(struct _Node));
    newNode->prev = NULL;
    newNode->data = val;

    // Find the first node
    struct _Node* firstNode = list;
    while (firstNode->prev != NULL) {
        firstNode = firstNode->prev;
    }

    // Link the new node into the list
    firstNode->prev = newNode;
    newNode->next = firstNode;
}

void freeList(List* list) {
    // Navigate to first node
    struct _Node* firstNode = list;
    while (firstNode->prev != NULL) {
        firstNode = firstNode->prev;
    }

    // Create two iterators, one which is used for deleting
    // other for navigating across the list
    struct _Node* navigatingIterator = firstNode;
    struct _Node* deletingIterator = NULL;

    while (navigatingIterator != NULL) {
        deletingIterator = navigatingIterator;
        navigatingIterator = navigatingIterator->next;

        free(deletingIterator);
    }
}