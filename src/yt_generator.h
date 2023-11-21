#ifndef YT_GENERATOR_H
#define YT_GENERATOR_H

#include "yt_parser.h"
#include "yt_file.h"

void write_token_data(const YT_Tokenized_data *token_data, const char* file_path);

#endif