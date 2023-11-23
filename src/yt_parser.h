#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_string.h"
#include "yt_vector.h"

enum TAG_TYPE
{
    TAG_NO_TYPE,
    TAG_TEMPLATE,

};

typedef enum TAG_TYPE TAG_TYPE;

enum TOKEN_TYPE
{
    NO_TYPE,
    FN_TYPE,
    FN_NAME,
    FN_TEM_LIST,
    FN_ARG_TYPE_LIST,
    FN_ARG_NAME_LIST,
    FUNCTION_BLOCK,
};

typedef enum TOKEN_TYPE TOKEN_TYPE;

struct YT_Tokenized_data
{
    YK_Yektor token;
    YK_Yektor type;
};

typedef struct YT_Tokenized_data YT_Tokenized_data;

struct tokenized_data_list
{
    YK_Yektor tokenized_data;
    YK_Yektor tags;
};

typedef struct tokenized_data_list tokenized_data_list;

void token_list_innit(tokenized_data_list *data);
void token_list_free(tokenized_data_list *data);

void token_data_innit(YT_Tokenized_data *data);
void token_data_free(YT_Tokenized_data *data);

void tokenize(const YT_String *in, tokenized_data_list *data);
void tokenize_template(char *in, YT_Tokenized_data *data);
TAG_TYPE get_tag_type(char *token);
void token_data_print(YT_Tokenized_data *data);

/*
    Solves no purpose. Don't use
*/
char *peek(char *in, char *delimiters);

#endif