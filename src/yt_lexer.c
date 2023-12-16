#include "yt_lexer.h"
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

        // skip whitespace
        if (tk.type == WHITE_SPACE)
        {
            advance(scanner, 1);
            continue;
        }

        yk_yektor_push(&scanner->token_list, &tk);

        advance(scanner, 1);
    }
    token tk_temp = {.lexeme = "EoF", .type = TK_EOF};

    yk_yektor_push(&scanner->token_list, &tk_temp);
    print_token_list(&scanner->token_list);
}

void print_token(token token)
{
    print_token_type(token.type);
    printf(": %s ", token.lexeme);
    printf("\n");
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

char *peek_word(scanner *scanner)
{
    int i = 0;
    char *eep = malloc(sizeof(char) * 20);
    while (peek(scanner, i) != ' ' && peek(scanner, i) != '\n' && peek(scanner, i) != ',')
    {
        // printf("%c", peek(scanner, 0));
        eep[i] = peek(scanner, i);
        i++;
    }
    eep = realloc(eep, (i + 1) * sizeof(char));
    eep[i] = '\0';

    return eep;
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
    case ':':
        out.lexeme = ":";
        out.type = COLON;
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

        /*
            check for struct instead of stopping at s.
            Alternatively, make a function that peeks the next "word", i.e,
            peeks until it finds whitespace
        */
        if (peek(scanner, 1) == 't')
        {
            out.lexeme = "@types";
            out.type = TAG_TYPES;
            advance(scanner, strlen(out.lexeme));
            break;
        }

        else if (peek(scanner, 1) == 'g')
        {
            out.lexeme = "@gen";
            out.type = TAG_GEN;
            advance(scanner, strlen(out.lexeme));
            break;
        }

        break;
    case '$':
        out.lexeme = "$";
        out.type = DOLLAR;
        break;
    case '`':
        out.lexeme = "`";
        out.type = BACK_TICK;
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
        if (isalpha(*current_char))
        {
            char *eep = peek_word(scanner);
            advance(scanner, strlen(eep));
            out.lexeme = eep;
            out.type = IDENTIFIER;
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

void print_token_type(token_type tt)
{
    const char *tt_string;
    switch (tt)
    {
    case LEFT_BRACE:
        tt_string = "Left Brace";
        break;
    case RIGHT_BRACE:
        tt_string = "Right Brace";
        break;
    case LEFT_PAREN:
        tt_string = "Left Parenthesis";
        break;
    case RIGHT_PAREN:
        tt_string = "Right Parenthesis";
        break;
    case WHITE_SPACE:
        tt_string = "White Space";
        break;
    case TAG_TYPES:
        tt_string = "Types Tag";
        break;
    case TAG_GEN:
        tt_string = "Tag - Generate";
        break;
    case IDENTIFIER:
        tt_string = "Identifier";
        break;
    case DOLLAR:
        tt_string = "Dollar Sign";
        break;
    case COLON:
        tt_string = "Colon";
        break;
    case BACK_TICK:
        tt_string = "Back Tick";
        break;
    case STRING:
        tt_string = "String";
        break;
    case TK_EOF:
        tt_string = "End of File";
        break;
    default:
        tt_string = "Unknown Token Type";
        break;
    }

    printf("%-15s", tt_string);
}
