#ifndef YT_STRING_H
#define YT_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct YT_String
{
    char *data;
    size_t length;
} YT_String;


void yt_string_innit(YT_String *str, const char *initial);
void yt_string_set(YT_String *str, const char *new_value);

void yt_string_free(YT_String *str);
YT_String yt_string_clone(const YT_String *str);


#endif