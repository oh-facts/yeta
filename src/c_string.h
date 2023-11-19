#ifndef C_STRING_H
#define C_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct C_String
{
    char *data;
    size_t length;
} C_String;


void string_innit(C_String *str, const char *initial);
void string_set(C_String *str, const char *new_value);

void string_free(C_String *str);
C_String string_clone(const C_String *str);


#endif