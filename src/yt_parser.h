#ifndef YT_PARSER_H
#define YT_PARSER_H

#include "yt_string.h"
#include "yt_vector.h"

typedef struct Chunks Chunks;
typedef struct struct_template struct_template;

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

/*
    Breaks the meta file content into separate chunks.
    each chunk is tag + block.
*/
void break_into_chunks(YT_String *meta_file_content, Chunks *chunks);

void print_chunks(const Chunks *chunks);

#endif