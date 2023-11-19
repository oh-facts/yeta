
#include "c_string.h"
void string_innit(C_String *str, const char *initial)
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

void string_set(C_String *str, const char *new_value)
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

void string_free(C_String *str)
{
    free(str->data);
    str->data = NULL;
    str->length = 0;
}

C_String string_clone(const C_String *str)
{
    C_String out;
    string_innit(&out, str->data);
    return out;
}
