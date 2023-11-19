/*
dynamic vector I lifted from a different project
*/

#ifndef YK_YEKTOR_H
#define YK_YEKTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Resizable.
    When you push to a yektor, the yektor creates a copy and is
    meant to own it. When pushing, it returns a ptr to it, incase
    you want to edit it.

    size:     number of elements currently stored

    capacity: number of elements for which space is allocated

    size <=capacity
    Must be freed with yk_yektor_destroy.
    But only if you want to free it.
    It is your choice. And your choice only.
*/
typedef struct YK_Yektor
{
    void *data;
    size_t element_size;
    size_t size;
    size_t capacity;
} YK_Yektor;

/*
    Initializes yektor. Resizing is "expensive". So try to make originial size as close to capacity
*/
void yk_yektor_innit(YK_Yektor *vector, size_t capacity, size_t element_size);

/*
    Pushes element to yektor. Yektor owns element now, and returns a reference to the element.
    This is a shallow copy!
*/
void *yk_yektor_push(YK_Yektor *vector, void *element);

/*
    Pushes element to yektor. Yektor owns element now, and returns a reference to the element.
    This is a deep copy!
*/
void *yk_yektor_push_deep(YK_Yektor *vector, void *element, void (*copy_element)(void *dest, const void *src));

/*
    Inserts element at index. Owns the element and returns a reference to the element.
    I haven't tested this. It might not work. LOL.
*/
void *yk_yektor_insert(YK_Yektor *vector, void *element, size_t index);

/*
    Modify an element at index.
*/
void yk_yektor_set(YK_Yektor *vector, void *element, size_t index);

/*
    Returns a pointer to the data at index
*/
void *yk_yektor_get(YK_Yektor *vector, size_t index);

/*
    Pop element.
*/
void yk_yektor_pop(YK_Yektor *vector);

/*
    Pop and get element. I haven't tested it yet.
*/
void *yk_yektor_pop_get(YK_Yektor *vector);

/*
    Frees all the data. This is a shallow destroy!
*/
void yk_yektor_destroy(YK_Yektor *vector);

/*
    Prints yektor meta data and memory addresses of the data.
*/
void yk_yektor_print(YK_Yektor *vector);

#endif