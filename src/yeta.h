#ifndef YETA_H
#define YETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "yt_vector.h"
#include "yt_file.h"
#include "yt_parser.h"
#include "yt_generator.h"

struct YT_State
{
    char *out_path;

    char *in_path;

};

typedef struct YT_State YT_State;


void yt_gen(YT_State *ceta_data, char *type);

#endif