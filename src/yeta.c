#include "yeta.h"
#include "yt_string.h"

void _replace_angled_brackets(char *input);
char *_replace(const char *string, const char *search, const char *replace);

void template_generator();
void template_writer(YT_State *state);
void template_list_print();

void find_generator();

void yt_remove_word(char *str, const char *word);

YK_Yektor meta_template_list;
YK_Yektor gen_template_list;

YT_String meta_data;

int main()
{
    YT_State cd;

    cd.in_path = "eep.meta";
    cd.out_path = "../sandbox/gen.h";

    yk_yektor_innit(&meta_template_list, 10, sizeof(YT_String));

    {
        char *temp = yt_file_reader(cd.in_path);
        yt_string_innit(&meta_data, temp);
        free(temp);
    }

    yt_file_clean(cd.out_path);

    YT_Tokenized_data td;
    token_data_innit(&td);

    tokenize(&meta_data, &td);
    write_token_data(&td, cd.out_path);

    // token_data_free(&td);

    // yt_gen(&cd, "int");
    //  printf("%d", meta_template_list.size);
    //  gen(&cd, "float");

    return 0;
}

void yt_gen(YT_State *ceta_data, char *type)
{

    // tokenize();

    template_generator();

    find_generator();

    // template_list_print();

    template_writer(ceta_data);
}

void template_generator()
{
    for (int i = 0; i < meta_template_list.size; i++)
    {
        YT_String *handle = yk_yektor_get(&meta_template_list, i);
        _replace_angled_brackets(handle->data);
        handle->data = _replace(handle->data, "T", "int");
    }
}

void template_writer(YT_State *state)
{
    for (int i = 0; i < meta_template_list.size; i++)
    {
        YT_String *handle = yk_yektor_get(&meta_template_list, i);
        yt_file_writer(state->out_path, handle->data);
    }
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
    int num = meta_template_list.size;
    for (int i = 0; i < num; i++)
    {
        YT_String *temp = yk_yektor_get(&meta_template_list, i);

        printf("-----%d---- \n", i);
        printf("%s \n", temp->data);
        printf("-----%d---- \n", i);
    }
}

void find_generator()
{
    for (int i = 0; i < meta_template_list.size; i++)
    {
        YT_String *handle = yk_yektor_get(&meta_template_list, i);
        YT_String temp = yt_string_clone(handle);

        char *token;
        char *context;

        const char delimiters[] = "\n";

        token = strtok_s(temp.data, delimiters, &context);
        // printf("%s \n", token);

        if (strcmp(token, "template") == 0)
        {
            token = strtok_s(NULL, delimiters, &context);
            // printf("%s \n", token);
            // printf("%s \n", temp.data);

            char *temp2 = (yt_string_clone(handle)).data;
            yt_remove_word(temp2, "template");

            // yt_remove_word(temp.data)

            yt_string_set(handle, temp2);

            free(temp2);
        }

        else if (strcmp(token, "nochange") == 0)
        {
            printf("peop");
        }

        yt_string_free(&temp);
    }
}

void yt_remove_word(char *str, const char *word)
{
    size_t wordLen = strlen(word);

    while ((str = strstr(str, word)) != NULL)
    {
        memmove(str, str + wordLen, strlen(str + wordLen) + 1);
    }
}
