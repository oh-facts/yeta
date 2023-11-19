
#include "c_string.h"

void string_innit(C_String *str, const char *initial)
{

    str->data = malloc(strlen(initial) + 1);

    if (str->data != NULL)
    {
        strcpy(str->data, initial);
        str->length = strlen(initial);
    }
    else
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void string_set(C_String *str, const char *new_value)
{
    str->data = realloc(str->data, strlen(new_value) + 1);
    if (str->data != NULL)
    {
        strcpy(str->data, new_value);
        str->length = strlen(new_value);
    }
    else
    {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

void string_free(C_String *str)
{
    free(str->data);
    str->data = NULL;
    str->length = 0;
}
