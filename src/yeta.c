#include "yeta.h"
#include "yt_string.h"

void _replace_angled_brackets(char *input);
char *_replace(const char *string, const char *search, const char *replace);
void tokenize();

void template_list_print();

YK_Yektor template_list;
YT_String meta_data;

int main()
{
    YT_State cd;

    cd.in_path = "eep.meta";
    cd.out_path = "../sandbox/gen.h";

    yk_yektor_innit(&template_list, 10, sizeof(YT_String));

    {
        char *temp = yt_file_reader(cd.in_path);
        yt_string_innit(&meta_data, temp);
        free(temp);
    }

    yt_file_clean(cd.out_path);

    yt_gen(&cd, "int");
    // gen(&cd, "float");

    return 0;
}

void tokenize()
{

    YT_String chunk;
    yt_string_innit(&chunk, "p");

    char *token;
    char *context;

    const char delimiters[] = "@";

    token = strtok_s(meta_data.data, delimiters, &context);

    while (token != NULL)
    {
        yt_string_set(&chunk, token);
        
        YT_String temp = yt_string_clone(&chunk);
        yk_yektor_push(&template_list, &temp);

        token = strtok_s(NULL, delimiters, &context);
    }

    // printf("%d \n", chunk.length);

    yt_string_free(&chunk);
    template_list_print();
}

void yt_gen(YT_State *ceta_data, char *type)
{
    YT_String *handle;
    {
        YT_String string;
        char *temp = yt_file_reader(ceta_data->in_path);
        yt_string_innit(&string, temp);
        free(temp);

        handle = yk_yektor_push(&template_list, &string);
        yt_string_free(&string);
    }

    tokenize();

    /*
        _replace_angled_brackets(handle->data);

        handle->data = _replace(handle->data, "T", type);

        yt_file_writer(ceta_data->out_path, handle->data);

    */
}

void _replace_angled_brackets(char *input)
{
    for (int i = 0; input[i]; i++)
    {
        if ((input[i] == '<' && input[i + 1] == 'T') || input[i] == '>' && input[i - 1] == 'T')
        {
            input[i] = '_';
        }
    }
}

char *_replace(const char *string, const char *search, const char *replace)
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

void template_list_print()
{
    int num = template_list.size;
    for (int i = 0; i < num; i++)
    {
        YT_String *temp = yk_yektor_get(&template_list, i);

        printf("-----%d---- \n", i);
        printf("%s \n", temp->data);
        printf("-----%d---- \n", i);
    }
}