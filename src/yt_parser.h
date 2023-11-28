#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_string.h"
#include "yt_vector.h"
#include <stdint.h>

#define true 1
#define false 0

typedef int8_t bool;

typedef struct Chunks Chunks;
typedef struct struct_template struct_template;
typedef struct scanner scanner;
typedef struct token token;

struct Chunks
{
    YK_Yektor struct_templates;
};

struct struct_template
{
    YT_String struct_name;
    YK_Yektor variable_names;
    YK_Yektor variable_types;
};

enum token_type
{
    NO_TYPE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    SEMICOLON,
    VAR_NAME,
    VAR_TYPE,
    TAG_STRUCT,
    WHITE_SPACE,
    STRUCT_NAME,
    TK_EOF
};

typedef enum token_type token_type;

struct token
{
    token_type type;
    const char *lexeme;
};

struct scanner
{
    const char *source;
    YK_Yektor token_list;
    int start;
    int current;
    int line;
};

void scanner_innit(scanner *scanner, const char *source_file_content);
void scan_tokens(scanner *scanner);
token make_token(scanner *scanner);
token get_token_start(scanner *scanner, int index);
token get_token_end(scanner *scanner, int index);
void print_token_list(const YK_Yektor* token_list);
void print_token(token token);
/*
    Returns character at string index (0 + ahead)
    use negative index to go backwards.
*/
char peek(scanner* scanner, int ahead);

void advance(scanner *scanner,int step);

bool is_at_end(scanner *scanner);

/*
    Breaks the meta file content into separate chunks.
    each chunk is tag + block.
*/
void break_into_chunks(YT_String *meta_file_content, Chunks *chunks);

void print_chunks(const Chunks *chunks);

#endif