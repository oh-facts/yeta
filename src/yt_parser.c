#include "yt_parser.h"

void yt_parse(YK_Yektor *tokens)
{
    token *current = yk_yektor_get(tokens, 0);
    int i = 0;

    while (current->type != TK_EOF)
    {
        printf("parsing token %d\n", i);
        i++;
        current = yk_yektor_get(tokens, i);
    }
}