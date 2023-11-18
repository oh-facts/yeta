#include "ceta.h"
/*
fopen_s() is only defined in windows
*/
#ifdef __unix
#define fopen_s(pFile, filepath, mode) ((*(pFile)) = fopen((filepath), (mode))) == NULL
#endif

char *yk_file_reader(const char *filepath);
void file_writer(const char *filepath, const char *data);
void _replace_angled_brackets(char *input);
char *_replace(const char *string, const char *search, const char *replace);

int main()
{
    file_clean("../src/gen.h");
    mp_state cd;
    cd.in_path = "eep.meta";
    cd.out_path = "../sandbox/gen.h";

    gen(&cd, "int");

    gen(&cd, "float");
    return 0;
}

void gen(mp_state *ceta_data, char *type)
{
    char *in_data = yk_file_reader(ceta_data->in_path);

    _replace_angled_brackets(in_data);

    in_data = _replace(in_data, "T", type);

    file_writer(ceta_data->out_path, in_data);

    free(in_data);
}

void _replace_angled_brackets(char *input)
{
    for (int i = 0; input[i]; i++)
    {
        if ((input[i] == '<' && input[i + 1] == 'T') || input[i] == '>' && input[i - 1] == 'T')
        {
            input[i] = '_';
        }
    }
}

char *_replace(const char *string, const char *search, const char *replace)
{
    char *result;
    int i, cnt = 0;
    size_t replaceLen = strlen(replace);
    size_t searchLen = strlen(search);

    for (i = 0; string[i] != '\0'; i++)
    {
        if (strstr(&string[i], search) == &string[i])
        {
            cnt++;

            i += searchLen - 1;
        }
    }

    result = (char *)malloc(i + cnt * (replaceLen - searchLen) + 1);

    i = 0;
    while (*string)
    {
        if (strstr(string, search) == string)
        {
            strcpy_s(&result[i], replaceLen + 1, replace);
            i += replaceLen;
            string += searchLen;
        }
        else
            result[i++] = *string++;
    }

    result[i] = '\0';
    return result;
}

void file_writer(const char *filepath, const char *data)
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

void file_clean(const char *filepath)
{
    FILE *file;
    fopen_s(&file, filepath, "w");
    fclose(file);
}

char *yk_file_reader(const char *filepath)
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