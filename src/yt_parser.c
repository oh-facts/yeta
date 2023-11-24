#include "yt_parser.h"
#include <ctype.h>

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

        while (result != 0)
        {
            // var type
            result = strtok_s(NULL, " ", &context);
            // printf("%s", result);
            if (strcmp(result, "};") == 0)
            {
                break;
            }

            {
                YT_String var_type;
                yt_string_innit(&var_type, result);
                yk_yektor_push(st_var_types_handle, &var_type);
            }

            // var name
            result = strtok_s(NULL, "\n", &context);
            // printf("%s", result);
            {
                YT_String var_name;
                yt_string_innit(&var_name, result);
                yk_yektor_push(st_var_names_handle, &var_name);
            }
        }
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
