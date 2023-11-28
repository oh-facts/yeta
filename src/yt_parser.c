#include "yt_parser.h"
#include <ctype.h>
// https://craftinginterpreters.com/introduction.html

// instead of doing what you do.
// implement a peek.
// that returns next token
// and read file like that

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
        // store lexemes.
        // make a hashmap.
        // store keywords
        // store identifiers

        token tk = make_token(scanner);
        if (tk.type == WHITE_SPACE)
        {
            advance(scanner, 1);
            continue;
        }

        yk_yektor_push(&scanner->token_list, &tk);

        advance(scanner, 1);
    }

    print_token_list(&scanner->token_list);
}

void print_token(token token)
{
    printf("%s %d \n", token.lexeme, token.type);
}

void print_token_list(const YK_Yektor *token_list)
{
    int size = token_list->size;
    for (int i = 0; i < size; i++)
    {
        token tk = *((token *)yk_yektor_get(token_list, i));
        print_token(tk);
    }
}

char peek(scanner *scanner, int ahead)
{
    return *(&scanner->source[scanner->current] + ahead);
}

void peek_next(scanner *scanner)
{
}

void advance(scanner *scanner, int step)
{
    scanner->current += step;
}

token make_token(scanner *scanner)
{
    token out;
    out.type = -1;
    out.lexeme = "INVALID_TYPE";

    const char *current_char = &(scanner->source[scanner->current]);

    // printf("%c", *current_char);
    switch (*current_char)
    {
    case '(':
        out.lexeme = "(";
        out.type = LEFT_PAREN;
        break;
    case ')':
        out.lexeme = ")";
        out.type = RIGHT_PAREN;
        break;
    case '{':
        out.lexeme = "{";
        out.type = LEFT_BRACE;
        break;
    case '}':
        out.lexeme = "}";
        out.type = RIGHT_BRACE;
        break;
    case ';':
        out.type = SEMICOLON;
        break;
    case '/':
        if (peek(scanner, 1) == '*')
        {
            out.type = WHITE_SPACE;
            advance(scanner, 2);
            // printf("comment starts");
            while (peek(scanner, 1) != '*' && peek(scanner, 2) != '/')
            {
                // printf("%c", peek(scanner, 0));
                advance(scanner, 1);
            }

            advance(scanner, 2);
            // printf("comment ends");
        }
        break;
    case '@':

        if (peek(scanner, 1) == 's')
        {
            out.lexeme = "struct";
            out.type = TAG_STRUCT;
            advance(scanner, strlen(out.lexeme));
        }

        break;
    /*
        fall through cases
    */
    case ' ':
    case '\n':
        out.lexeme = "WHITE_SPACE";
        out.type = WHITE_SPACE;
        break;

    default:
        if (isalpha(*current_char) && get_token_end(scanner, 0).type == TAG_STRUCT)
        {

            int i = 0;
            char *eep = malloc(sizeof(char) * 20);
            while (isalnum(peek(scanner, 0)) || peek(scanner, 0) == '_')
            {
                // printf("%c", peek(scanner, 0));
                eep[i] = peek(scanner, 0);
                advance(scanner, 1);
                i++;
            }
            eep = realloc(eep, (i + 1) * sizeof(char));
            eep[i] = '\0';

            // printf("%d", i);

            out.lexeme = eep;
            out.type = STRUCT_NAME;
            //  advance(scanner, i-1);
            break;
        }
        out.lexeme = current_char;
        out.type = NO_TYPE;
        // printf("%c", *current_char);
        break;
    }

    return out;
}

token get_token_start(scanner *scanner, int index)
{
    return *(token *)(yk_yektor_get(&scanner->token_list, index));
}

token get_token_end(scanner *scanner, int index)
{
    return *(token *)(yk_yektor_get(&scanner->token_list, scanner->token_list.size - index - 1));
}

bool is_at_end(scanner *scanner)
{
    return scanner->current >= strlen(scanner->source);
}