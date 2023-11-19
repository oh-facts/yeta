#include "ceta.h"
#include "c_string.h"
/*
fopen_s() is only defined in windows
*/
#ifdef __unix
#define fopen_s(pFile, filepath, mode) ((*(pFile)) = fopen((filepath), (mode))) == NULL
#endif

char *file_reader(const char *filepath);
void file_writer(const char *filepath, const char *data);
void _replace_angled_brackets(char *input);
char *_replace(const char *string, const char *search, const char *replace);
void tokenize();

void template_list_print();

YK_Yektor template_list;
C_String meta_data;

int main()
{
    mp_state cd;

    cd.in_path = "eep.meta";
    cd.out_path = "../sandbox/gen.h";

    yk_yektor_innit(&template_list, 10, sizeof(C_String));

    {
        char *temp = file_reader(cd.in_path);
        string_innit(&meta_data, temp);
        free(temp);
    }

    file_clean(cd.out_path);

    gen(&cd, "int");
    // gen(&cd, "float");

    return 0;
}

void tokenize()
{

    C_String chunk;
    string_innit(&chunk, "p");

    char *token;
    char *context;

    const char delimiters[] = "@";

    token = strtok_s(meta_data.data, delimiters, &context);

    while (token != NULL)
    {
        string_set(&chunk, token);
        
        C_String temp = string_clone(&chunk);
        yk_yektor_push(&template_list, &temp);

        token = strtok_s(NULL, delimiters, &context);
    }

    // printf("%d \n", chunk.length);

    string_free(&chunk);
    template_list_print();
}

void gen(mp_state *ceta_data, char *type)
{
    C_String *handle;
    {
        C_String string;
        char *temp = file_reader(ceta_data->in_path);
        string_innit(&string, temp);
        free(temp);

        handle = yk_yektor_push(&template_list, &string);
        string_free(&string);
    }

    tokenize();

    /*
        _replace_angled_brackets(handle->data);

        handle->data = _replace(handle->data, "T", type);

        file_writer(ceta_data->out_path, handle->data);

    */
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

char *file_reader(const char *filepath)
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

void template_list_print()
{
    int num = template_list.size;
    for (int i = 0; i < num; i++)
    {
        C_String *temp = yk_yektor_get(&template_list, i);

        printf("-----%d---- \n", i);
        printf("%s \n", temp->data);
        printf("-----%d---- \n", i);
    }
}