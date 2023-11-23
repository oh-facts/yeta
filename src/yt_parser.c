#include "yt_parser.h"

void token_list_innit(tokenized_data_list *data)
{
    yk_yektor_innit(&data->tokenized_data, 1, sizeof(YT_Tokenized_data));

    YT_Tokenized_data *handle = &((YT_Tokenized_data *)data->tokenized_data.data)[0];
    token_data_innit(handle);

    yk_yektor_innit(&data->tokenized_data, 1, sizeof(YT_Tokenized_data));
}

void token_list_free(tokenized_data_list *data)
{

    for (int i = 0; i < data->tokenized_data.capacity; i++)
    {
        YT_Tokenized_data *handle = &((YT_Tokenized_data *)data->tokenized_data.data)[i];
        token_data_free(handle);
    }

    yk_yektor_destroy(&data->tokenized_data);
    yk_yektor_destroy(&data->tags);
}

void token_data_innit(YT_Tokenized_data *data)
{
    yk_yektor_innit(&data->token, 5, sizeof(YT_String));
    yk_yektor_innit(&data->type, 5, sizeof(TAG_TYPE));
}

void tokenize(const YT_String *in, tokenized_data_list *data)
{
    char *token;
    char *context;

    const char delimiters[] = "@";

    YT_String temp_in = yt_string_clone(in);

    token = strtok_s(temp_in.data, delimiters, &context);

    int count = 0;
    while (1)
    {
        token = strtok_s(NULL, delimiters, &context);
        if (token == NULL)
        {
            break;
        }
        // printf("%s", token);
        {
            token = strtok_s(NULL, "\n", &context);
            if (token == NULL)
            {
                break;
            }

            TAG_TYPE temp_type = get_tag_type(token);
            void *temp_type_ptr = &temp_type;

            YK_Yektor *tag_handle = &((YK_Yektor *)data->tokenized_data.data)[count];
            yk_yektor_innit(tag_handle, 1, sizeof(YK_Yektor));

            yk_yektor_push(tag_handle, temp_type_ptr);

            // if template tag
            if (temp_type == 1)
            {
                YT_Tokenized_data td;
                token_data_innit(&td);
                tokenize_template(token,&td);
                token_data_print(&td);
            }
        }

        //        yk_yektor_push(data.)

        // tokenize_template(token, &td);
        // token_data_print(&td);
        // printf("%s ", token);

        // printf("%s ", (&(YT_Tokenized_data *)td.token.data)[count]->token.data);

        // token_data_print(&td);

        // YT_Tokenized_data *handle = &((YT_Tokenized_data *)data->tokenized_data.data)[count];
        // YK_Yektor *handle = (&data->tokenized_data.data)[count];

        // yk_yektor_push(handle, &td);
        // printf("%s", token);

        // printf("%s ",&data->tokenized_data.data);

        printf("------- \n");
        count++;
    }

    // token_data_print(&((YT_Tokenized_data *)data->tokenized_data.data)[0]);
    //    token_data_print(&((YT_Tokenized_data *)data->tokenized_data.data)[1]);
    //    token_data_print(&((YT_Tokenized_data *)data->tokenized_data.data)[2]);
}

void tokenize_template(char *in, YT_Tokenized_data *data)
{

    char *token;
    char *context;

    const char delimiters[] = "@";

    // printf("%s ", in->data);
    token = strtok_s(in, "@", &context);
    printf("%s ", token);

    int count = 0;
    while (1)
    {

        token = strtok_s(NULL, "\n", &context);
        if (token == NULL)
        {
            break;
        }

        TAG_TYPE temp_type = get_tag_type(token);
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

        // printf("%s ", func_block.data);

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

TAG_TYPE get_tag_type(char *token)
{

    if (strcmp(token, "template") == 0)
    {
        return TAG_TEMPLATE;
    }

    return TAG_NO_TYPE;
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
