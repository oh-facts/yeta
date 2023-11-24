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

char *yt_string_replace_word(const char *string, const char *search, const char *replace)
{
    char *result;
    int i, cnt = 0;
    size_t replaceLen = strlen(replace);
    size_t searchLen = strlen(search);

    for (i = 0; string[i] != '\0'; i++)
    {
        if (strstr(&string[i], search) == &string[i])
        {
            cnt++;

            i += searchLen - 1;
        }
    }

    result = (char *)malloc(i + cnt * (replaceLen - searchLen) + 1);

    i = 0;
    while (*string)
    {
        if (strstr(string, search) == string)
        {
            strcpy_s(&result[i], replaceLen + 1, replace);
            i += replaceLen;
            string += searchLen;
        }
        else
            result[i++] = *string++;
    }

    result[i] = '\0';
    return result;
}

char *cstring_clone(const char *str)
{
    int size = strlen(str) + 1;

    char *out = malloc(size);
    if (!out)
    {
        perror("cstring clone failed: Not enough memory");
        exit(EXIT_FAILURE);
    }

    strcpy_s(out, size, str);
    if (!out)
    {
        perror("cstring clone failed: Copy failed");
        exit(EXIT_FAILURE);
    }

    return out;
}

char *peek(const char *in)
{
    char *out_token;
    char *context;

    char *in_temp = cstring_clone(in);

    while (isspace(*in_temp))
    {
        in_temp++;
    }

    in_temp = strtok_s(in_temp, "}", &context);
    printf("%s ", in_temp);
    in_temp = strtok_s(NULL, " ", &context);
    printf("%s ", in_temp);

    return in_temp;
}