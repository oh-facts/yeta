#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_lexer.h"
#include "yt_vector.h"

typedef struct ast_node ast_node;
typedef struct ast_table ast_table;

struct ast_table
{
    ast_node *types;
    token name;
    int member_count;
};

struct ast_node
{
    int type;
    ast_node* next;
    union
    {
        ast_table table;
    };
};

void yt_parse(YK_Yektor *tokens);

#endif