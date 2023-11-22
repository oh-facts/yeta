#include "yt_parser.h"

void chunk_innit(chunk *data)
{
    yk_yektor_innit(&data->tokenized_data, 5, sizeof(YT_Tokenized_data));
    token_data_innit(&data->tokenized_data);

    yk_yektor_innit(&data->tag_type, 5, sizeof(TAG_TYPE));
}

void chunk_free(chunk *data)
{
    
}

void token_data_innit(YT_Tokenized_data *data)
{
    yk_yektor_innit(&data->token, 5, sizeof(YT_String));
    yk_yektor_innit(&data->token_type, 5, sizeof(TOKEN_TYPE));
}

void tokenize(const YT_String *in, YT_Tokenized_data *data)
{
    char *last_token;
    char *token;

    char *context;

    /*
        I am making some bold assumptions atm.
        The assumption is that tag comes first, then rest of the function.
        This assumption should always be satisfied since it wouldn't make sense
        if it didn't.
    */
    char *delimmiter_list[] = {"@", "\n"};
    token = strtok_s(in->data, delimmiter_list[0], &context);

    int count = 0;
    while (1)
    {

        // rest of the function
        token = strtok_s(NULL, delimmiter_list[1], &context);
        if (token == NULL)
        {
            break;
        }

        TOKEN_TYPE temp_type = get_token_type(token);
        void *temp_type_ptr = &temp_type;
        yk_yektor_push(&data->token_type, temp_type_ptr);

        // Tag token
        token = strtok_s(NULL, delimmiter_list[0], &context);
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
    for (int i = 0; i < data->token_type.size; i++)
    {
        YT_String temp_token = ((YT_String *)data->token.data)[i];
        printf("%s \n", temp_token.data);

        int temp_type = ((int *)data->token_type.data)[i];
        printf("%d \n", temp_type);
    }
}

TOKEN_TYPE get_token_type(char *token)
{

    if (strcmp(token, "template") == 0)
    {
        return TAG_TEMPLATE;
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
    yk_yektor_destroy(&data->token_type);
}
