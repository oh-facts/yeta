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
    TAG,
    FUNC_NAME,
    FUNC_LIST,
    FUNC_BLOCK,
};

typedef enum TOKEN_TYPE TOKEN_TYPE;

struct YT_Tokenized_data
{
    YK_Yektor token;
    YK_Yektor token_type;
};

typedef struct YT_Tokenized_data YT_Tokenized_data;

struct chunk
{
    //block
    YK_Yektor tokenized_data;
    YK_Yektor tag_type;
};

typedef struct chunk chunk;

void chunk_innit(chunk *data);
void chunk_free(chunk *data);

void token_data_innit(YT_Tokenized_data *data);
void token_data_free(YT_Tokenized_data *data);

void chunk_tokenize(const YT_String *in, chunk *chun);

void tokenize(const YT_String *in, YT_Tokenized_data *data);
TOKEN_TYPE get_token_type(char *token);
void token_data_print(YT_Tokenized_data *data);

/*
    Solves no purpose. Don't use
*/
char *peek(char *in, char *delimiters);

#endif