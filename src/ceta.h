#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct mp_state
{
    char *out_path;

    char *in_path;

};

typedef struct mp_state mp_state;


void gen(mp_state *ceta_data, char *type);

void file_clean(const char *filepath);