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

/*
    Allocates space for the initial and sets it to data.
    Sets length to strlen(initial) + 1

    Set directly incase you don't want to deep clone
*/
void yt_string_innit(YT_String *str, const char *initial);
void yt_string_set(YT_String *str, const char *new_value);

void yt_string_free(YT_String *str);
YT_String yt_string_clone(const YT_String *str);


char *yt_string_replace_word(const char *string, const char *search, const char *replace);
char *cstring_clone(char *str);
#endif