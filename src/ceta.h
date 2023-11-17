#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLEAN (1 << 0)

struct ceta_data
{
    char *gf_name;

    char *cf_name;
    char *cf_data;
    int flags;
    char *types;
};

typedef struct ceta_data ceta_data;

void generator_run();
