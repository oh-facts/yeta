#include "yeta.h"
#include "yt_string.h"

void yt_remove_word(char *str, const char *word);

YT_String meta_data;

void peek_tests();
void get_last_token_test();

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

    // Chunks chunks;
    //  break_into_chunks(&meta_data, &chunks);

    scanner sc;
    scanner_innit(&sc, meta_data.data);
    scan_tokens(&sc);

    // peek_tests();
    //get_last_token_test();
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

void peek_tests()
{
    scanner sc;
    scanner_innit(&sc, "hello hi i am a 2019 guy");
    advance(&sc, 1);
    char ee = peek(&sc, 1);
    printf("%c", ee);
}

void get_last_token_test()
{
    scanner sc;
    scanner_innit(&sc, "@struct {}");
    scan_tokens(&sc);

    token tk = get_token_end(&sc,0);
    print_token(tk);
}