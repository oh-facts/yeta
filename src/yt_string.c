#include "yt_string.h"
void yt_string_innit(YT_String *str, const char *initial)
{
    str->data = malloc(strlen(initial) + 1);

    if (str->data != NULL)
    {
        if (strcpy_s(str->data, strlen(initial) + 1, initial) == 0)
        {
            str->length = strlen(initial);
        }
        else
        {
            fprintf(stderr, "String copy failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void yt_string_set(YT_String *str, const char *new_value)
{   
    str->data = realloc(str->data, strlen(new_value) + 1);
    if (str->data != NULL)
    {
        if (strcpy_s(str->data, strlen(new_value) + 1, new_value) == 0)
        {
            str->length = strlen(new_value);
        }
        else
        {
            fprintf(stderr, "String copy failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void yt_string_free(YT_String *str)
{
    free(str->data);
    str->data = NULL;
    str->length = 0;
}

YT_String yt_string_clone(const YT_String *str)
{
    YT_String out;
    yt_string_innit(&out, str->data);
    return out;
}
