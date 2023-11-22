#include "yt_generator.h"

void write_token_data(const YT_Tokenized_data *token_data, const char *file_path)
{
    int size = token_data->token.size;
    for (int i = 0; i < size; i++)
    {
        char *temp_1 = ((YT_String *)token_data->token.data)[i].data;
        yt_file_writer(file_path, temp_1);
    }

    printf("%d \n", size);
}