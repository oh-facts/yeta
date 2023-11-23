#include "yt_parser.h"
#include "yt_file.h"

void token_data_innit(YT_Tokenized_data *data)
{
    yk_yektor_innit(&data->blocks, 5, sizeof(YK_Yektor));
    yk_yektor_innit(&data->tag_types, 5, sizeof(TOKEN_TYPE));

}

void tokenize(const YT_String *in, YT_Tokenized_data *data)
{

    char *token;
    char *context;

    const char delimiters[] = "@";

    token = strtok_s(in->data, delimiters, &context);
    yt_file_writer("../sandbox/gen.h", token);
    int count = 0;

    while (1)
    {

        token = strtok_s(NULL, "\n", &context);
        if (token == NULL)
        {
            break;
        }
        printf("%s ", token);
        printf("---");

        TOKEN_TYPE temp_type = get_token_type(token);
        void *temp_type_ptr = &temp_type;
        yk_yektor_push(&data->tag_types, temp_type_ptr);

        token = strtok_s(NULL, delimiters, &context);
        if (token == NULL)
        {
            break;
        }
        YT_String func_block;
        yt_string_innit(&func_block, token);
        yk_yektor_push(&data->blocks, &func_block);
        count++;
    }

    token_data_print(data);
}

void token_data_print(YT_Tokenized_data *data)
{
    for (int i = 0; i < data->tag_types.size; i++)
    {
        YT_String temp_token = ((YT_String *)data->blocks.data)[i];
        printf("%s \n", temp_token.data);

        int temp_type = ((int *)data->tag_types.data)[i];
        printf("%d \n", temp_type);
    }
}

TOKEN_TYPE get_token_type(char *token)
{

    if (strcmp(token, "template") == 0)
    {
        return TAG;
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

    for (int i = 0; i < data->blocks.capacity; i++)
    {
        yt_string_free(yk_yektor_get(&data->blocks, i));
    }

    yk_yektor_destroy(&data->blocks);
    yk_yektor_destroy(&data->tag_types);
}
