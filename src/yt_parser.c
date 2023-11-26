#include "yt_parser.h"
#include <ctype.h>
// https://craftinginterpreters.com/introduction.html

// instead of doing what you do.
// implement a peek.
// that returns next token
// and read file like that

void break_into_chunks(YT_String *meta_file_content, Chunks *chunks)
{

    {
        yk_yektor_innit(&chunks->struct_templates, 1, sizeof(struct_template));

        struct_template st;
        yk_yektor_innit(&st.variable_names, 1, sizeof(YT_String));
        yk_yektor_innit(&st.variable_types, 1, sizeof(YT_String));

        YT_String string;
        yt_string_innit(&string, "fe");
        st.struct_name = string;
        yt_string_innit(&st.struct_name, "default_struct");

        yk_yektor_push(&chunks->struct_templates, &st);
    }

    {
        YT_String data = yt_string_clone(meta_file_content);
        char *context;
        // upto @
        char *result = strtok_s(data.data, "@", &context);

        // catch tag_type
        result = strtok_s(NULL, "\n", &context);
        // printf("%s ", result);
        if (strcmp(result, "struct") == 0)
        {

            result = strtok_s(NULL, "\n", &context);
            // printf("%s ", result);

            struct_template *st_handle = yk_yektor_get(&chunks->struct_templates, 0);
            YK_Yektor *st_var_names_handle = &st_handle->variable_names;
            YK_Yektor *st_var_types_handle = &st_handle->variable_types;

            YT_String *name_handle = &st_handle->struct_name;
            yt_string_set(name_handle, result);

            // bracket open
            result = strtok_s(NULL, " ", &context);
            int count = 0;

            while (1)
            {
                // var type
                result = strtok_s(NULL, " ", &context);
                if (!result)
                {
                    break;
                }

                {

                    char *result_c = cstring_clean(result);

                    // printf("%s", result);
                    if (strcmp(result_c, "};") == 0)
                    {
                        break;
                    }
                    if (strcmp(result_c, "") == 0)
                    {
                        break;
                    }

                    YT_String var_type;
                    yt_string_innit(&var_type, result_c);
                    yk_yektor_push(st_var_types_handle, &var_type);
                    free(result_c);
                }

                // var name
                result = strtok_s(NULL, "\n", &context);
                if (!result)
                {
                    break;
                }

                {

                    char *result_c = cstring_clean(result);
                    if (strcmp(result_c, "};") == 0)
                    {
                        break;
                    }
                    if (strcmp(result_c, "") == 0)
                    {
                        break;
                    }
                    YT_String var_name;
                    yt_string_innit(&var_name, result_c);
                    yk_yektor_push(st_var_names_handle, &var_name);
                    free(result_c);
                }
                count++;
            }
        }
        yt_string_free(&data);
    }

    {
        YT_String data = yt_string_clone(meta_file_content);

        char *context;

        // upto @
        char *result = strtok_s(data.data, "@", &context);
        result = strtok_s(NULL, "@", &context);
        result = strtok_s(NULL, "@", &context);
        result = strtok_s(NULL, "\n", &context);
        printf("%s", result);
        // printf("%s ", result);
        if (strcmp(result, "struct") == 0)
        {

            result = strtok_s(NULL, "\n", &context);
            //    printf("%s ", result);

            struct_template *st_handle = yk_yektor_get(&chunks->struct_templates, 1);
            YK_Yektor *st_var_names_handle = &st_handle->variable_names;
            YK_Yektor *st_var_types_handle = &st_handle->variable_types;

            YT_String *name_handle = &st_handle->struct_name;
            yt_string_set(name_handle, result);

            // bracket open
            result = strtok_s(NULL, " ", &context);
            int count = 0;

            while (1)
            {
                // var type
                result = strtok_s(NULL, " ", &context);
                if (!result)
                {
                    break;
                }

                {

                    char *result_c = cstring_clean(result);

                    // printf("%s", result);
                    if (strcmp(result_c, "};") == 0)
                    {
                        break;
                    }
                    if (strcmp(result_c, "") == 0)
                    {
                        break;
                    }

                    YT_String var_type;
                    yt_string_innit(&var_type, result_c);
                    yk_yektor_push(st_var_types_handle, &var_type);
                    free(result_c);
                }

                // var name
                result = strtok_s(NULL, "\n", &context);
                if (!result)
                {
                    break;
                }

                {

                    char *result_c = cstring_clean(result);
                    if (strcmp(result_c, "};") == 0)
                    {
                        break;
                    }
                    if (strcmp(result_c, "") == 0)
                    {
                        break;
                    }
                    YT_String var_name;
                    yt_string_innit(&var_name, result_c);
                    yk_yektor_push(st_var_names_handle, &var_name);
                    free(result_c);
                }
                count++;
            }
        }
        yt_string_free(&data);
    }

    print_chunks(chunks);
}

void print_chunks(const Chunks *chunks)
{

    int num = chunks->struct_templates.size;

    for (int i = 0; i < num; i++)
    {

        struct_template *st_handle = yk_yektor_get(&chunks->struct_templates, i);
        YT_String *name_handle = &st_handle->struct_name;
        printf("chunk tag name: %s\n", name_handle->data);

        YK_Yektor *st_var_names_handle = &st_handle->variable_names;
        YK_Yektor *st_var_types_handle = &st_handle->variable_types;

        int num2 = st_var_names_handle->size;

        for (int j = 0; j < num2; j++)
        {
            YT_String *type_handle = yk_yektor_get(st_var_types_handle, j);
            printf("var type %d: %s\n", j, type_handle->data);

            YT_String *name_handle = yk_yektor_get(st_var_names_handle, j);
            printf("var name %d: %s\n", j, name_handle->data);
        }

        printf("------\n");
    }
}

void scanner_innit(scanner *scanner, const char *source_file_content)
{
    scanner->source = source_file_content;
    yk_yektor_innit(&scanner->token_list, 1, sizeof(token));
    scanner->start = 0;
    scanner->current = 0;
    scanner->line = 1;
}

void scan_tokens(scanner *scanner)
{
    while (!is_at_end(scanner))
    {
        char current_char = scanner->source[scanner->current];
        // printf("%c", current_char);
        // printf("%d", get_token_type(&current_char));
        scanner->current++;
        token_type tk = get_token_type(&current_char);
        yk_yektor_push(&scanner->token_list, &tk);
        advance(scanner);
    }

    print_token_list(&scanner->token_list);
}

void print_token_list(const YK_Yektor *token_list)
{
    int size = token_list->size;
    for (int i = 0; i < size; i++)
    {
        token_type tk = *((token_type *)yk_yektor_get(token_list, i));
        printf("%d", tk);
    }
}

char peek(const char *str, int ahead)
{
    return *(str + ahead);
}

void peek_next(scanner *scanner)
{
}

void advance(scanner *scanner)
{
}

token_type get_token_type(const char *str)
{
    token_type out = NO_TYPE;
    switch (*str)
    {
    case '(':
        out = LEFT_PAREN;
        break;
    case ')':
        out = RIGHT_PAREN;
        break;
    case '{':
        out = LEFT_BRACE;
        break;
    case '}':
        out = RIGHT_BRACE;
        break;
    case ';':
        out = SEMICOLON;
        break;
    default:
        break;
    }
    return out;
}

bool is_at_end(scanner *scanner)
{
    return scanner->current >= strlen(scanner->source);
}