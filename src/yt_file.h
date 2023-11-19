#ifndef YT_FILE_H
#define YT_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Reads a file at filepath and retuns data as a char *
    The returned char* needs to be freed by the caller.
*/
char *yt_file_reader(const char *filepath);

/*
    Writes data to the file at file path. Writes in 'a' mode
*/
void yt_file_writer(const char *filepath, const char *data);

/*
    Cleans file at filepath
*/
void yt_file_clean(const char *filepath);

#endif