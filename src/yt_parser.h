#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_string.h"
#include "yt_vector.h"

enum TOKEN_TYPE
{
    NO_TYPE,
    TAG,
    FUNCTION_BLOCK,
};

typedef enum TOKEN_TYPE TOKEN_TYPE;

struct YT_Tokenized_data
{
    YK_Yektor blocks;      //yektor of fn_data
    YK_Yektor tag_types;  //int
};

typedef struct YT_Tokenized_data YT_Tokenized_data;

struct fn_data
{
    YK_Yektor names;  //string
    YK_Yektor block;  //string
};

typedef struct fn_data fn_data;

void token_data_innit(YT_Tokenized_data *data);
void token_data_free(YT_Tokenized_data *data);

void tokenize(const YT_String *in, YT_Tokenized_data *data);
TOKEN_TYPE get_token_type(char *token);
void token_data_print(YT_Tokenized_data *data);

/*
    Solves no purpose. Don't use
*/
char *peek(char *in, char *delimiters);

#endif