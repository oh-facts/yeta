#include "yt_file.h"

/*
fopen_s() is only defined in windows
*/
#ifdef __unix
#define fopen_s(pFile, filepath, mode) ((*(pFile)) = fopen((filepath), (mode))) == NULL
#endif

void yt_file_writer(const char *filepath, const char *data)
{

    FILE *file;
    fopen_s(&file, filepath, "a");

    if (file == NULL)
    {
        perror("Error opening the output file");
    }

    fprintf(file, "%s\n", data);

    fclose(file);
}

char *yt_file_reader(const char *filepath)
{
    FILE *file;
    fopen_s(&file, filepath, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Error: Unable to open the file %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (length == 0)
    {
        fprintf(stderr, "Error: File is empty\n");
        fclose(file);
        return NULL;
    }

    char *string = malloc(sizeof(char) * (length + 1));
    if (string == NULL)
    {
        fprintf(stderr, "Error: File reader malloc failed for file %s\n", filepath);
        fclose(file);
        return NULL;
    }

    char c;
    int i = 0;

    while ((c = fgetc(file)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';

    fclose(file);

    return string;
}

void yt_file_clean(const char *filepath)
{
    FILE *file;
    fopen_s(&file, filepath, "w");
    fclose(file);
}
