#include "yt_parser.h"

void token_data_innit(YT_Tokenized_data *data)
{
    yk_yektor_innit(&data->token, 5, sizeof(YT_String));
    yk_yektor_innit(&data->type, 5, sizeof(TOKEN_TYPE));
}

void tokenize(const YT_String *in, YT_Tokenized_data *data)
{

    char *token;
    char *context;

    const char delimiters[] = "@";

    token = strtok_s(in->data, delimiters, &context);

    int count = 0;
    while (1)
    {

        token = strtok_s(NULL, "\n", &context);
        if (token == NULL)
        {
            break;
        }

        TOKEN_TYPE temp_type = get_token_type(token);
        void *temp_type_ptr = &temp_type;
        yk_yektor_push(&data->type, temp_type_ptr);

        token = strtok_s(NULL, delimiters, &context);
        if (token == NULL)
        {
            break;
        }
        YT_String func_block;
        yt_string_innit(&func_block, token);
        yk_yektor_push(&data->token, &func_block);
        count++;
    }

    // token_data_print(data);
}

void token_data_print(YT_Tokenized_data *data)
{
    for (int i = 0; i < data->type.size; i++)
    {
        YT_String temp_token = ((YT_String *)data->token.data)[i];
        printf("%s \n", temp_token.data);

        int temp_type = ((int *)data->type.data)[i];
        printf("%d \n", temp_type);
    }
}

TOKEN_TYPE get_token_type(char *token)
{

    if (strcmp(token, "template") == 0)
    {
        return TEMPLATE;
    }

    return NO_TYPE;
}

char *peek(char *in, char *delimiters)
{
    char *out_token;
    char *context;

    out_token = strtok_s(in, delimiters, &context);

    return out_token;
}

void token_data_free(YT_Tokenized_data *data)
{
    // later, allow vector to accept function pointer to destroy

    for (int i = 0; i < data->token.capacity; i++)
    {
        yt_string_free(yk_yektor_get(&data->token, i));
    }

    yk_yektor_destroy(&data->token);
    yk_yektor_destroy(&data->type);
}
