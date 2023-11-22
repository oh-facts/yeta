#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_string.h"
#include "yt_vector.h"

enum TOKEN_TYPE
{
    NO_TYPE,
    TEMPLATE,
    FUNCTION_BLOCK,
};

typedef enum TOKEN_TYPE TOKEN_TYPE;

struct YT_Tokenized_data
{
    YK_Yektor token;
    YK_Yektor type;
};

typedef struct YT_Tokenized_data YT_Tokenized_data;

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