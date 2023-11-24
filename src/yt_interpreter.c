#include "yt_interpreter.h"
/*
void interpret_tokenized_date(YT_Tokenized_data *data)
{
    int num = data->token.size;

    for (int i = 0; i < num; i++)
    {
        YT_String *handle = &((YT_String *)data->token.data)[i];
        
        char *temp = yt_string_replace_word(handle->data, "<T>", "_int");
        yt_string_set(handle, temp);
        free(temp);

        temp = yt_string_replace_word(handle->data, "T", "int");
        yt_string_set(handle, temp);
        free(temp);
    }
}
*/