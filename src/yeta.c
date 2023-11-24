#include "yeta.h"
#include "yt_string.h"

char *_replace(const char *string, const char *search, const char *replace);

void template_generator();
void template_writer(YT_State *state);
void template_list_print();

void find_generator();

void yt_remove_word(char *str, const char *word);

YT_String meta_data;

int main()
{
    YT_State cd;

    cd.in_path = "eep.meta";
    cd.out_path = "../sandbox/gen.h";

    {
        char *temp = yt_file_reader(cd.in_path);
        yt_string_innit(&meta_data, temp);
        free(temp);
    }

    yt_file_clean(cd.out_path);

    Chunks chunks;
    break_into_chunks(&meta_data, &chunks);

    

    // token_data_free(&td);

    // yt_gen(&cd, "int");
    //  printf("%d", meta_template_list.size);
    //  gen(&cd, "float");

    return 0;
}

void yt_remove_word(char *str, const char *word)
{
    size_t wordLen = strlen(word);

    while ((str = strstr(str, word)) != NULL)
    {
        memmove(str, str + wordLen, strlen(str + wordLen) + 1);
    }
}
