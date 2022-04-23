/*  CTM - C TO MIPS
 *  Copyright (c) 2022 Leonardo Z. Nunes
 *
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctm_token.h"

TokenType_t
ctm_token_typer(Token_t t)
{
    switch (t.value[0])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return CONSTANT_TK;
        case ',':
            return COMMA_TK;
        case '\"':
            return STRING_TK;
        case '{':
            return RBRACE_TK;
        case '}':
            return LBRACE_TK;
        case '(':
            return RPAREN_TK;
        case ')':
            return LPAREN_TK;
        case '\n':
            return LINEFEED_TK;
        case '+':
            return PLUS_TK;
        case '-':
            return MINUS_TK;
        case '/':
            return DIV_TK;
        case '*':
            return MULT_TK;
        case '|':
            return OR_TK;
        case '=':
        {
            if (t.value[1] && t.value[1] == '=')
                {
                    return EQUAL_TO_TK;
                }
            return EQUAL_TK;
        }
        case '&':
        {
            if (t.value[1] && t.value[1] == '&')
                {
                    return AND_TK;
                }
            return AND_ADDR_TK;
        }
        case '!':
        {
            if (t.value[1] && t.value[1] == '=')
                {
                    return NOT_EQUAL_TK;
                }
            return NOT_TK;
        }
        case '>':
        {
            if (t.value[1] && t.value[1] == '=')
                {
                    return GT_EQUAL_TK;
                }
            return GT_TK;
        }
        case '<':
        {
            if (t.value[1] && t.value[1] == '=')
                {
                    return LT_EQUAL_TK;
                }
            return LT_TK;
        }
        case ';':
            return SEMICOLON_TK;
        default:
            break;
        }

    if (strcmp(t.value, "main") == 0) return MAIN_TK;
    if (strcmp(t.value, "int") == 0) return INT_TK;
    if (strcmp(t.value, "void") == 0) return VOID_TK;
    if (strcmp(t.value, "return") == 0) return RETURN_TK;

    return IDENTIFIER_TK;
}

_Bool
is_dtype(TokenType_t tk)
{
    if (tk == VOID_TK ||
            tk == INT_TK ||
            tk == STRING_TK)
        {
            return 1;
        }
    return 0;
}

_Bool
is_operator(TokenType_t tk)
{
    if (tk == PLUS_TK ||
            tk == MINUS_TK ||
            tk == MULT_TK ||
            tk == DIV_TK ||
            tk == OR_TK ||
            tk == LT_TK ||
            tk == GT_TK ||
            tk == LT_EQUAL_TK ||
            tk == GT_EQUAL_TK ||
            tk == EQUAL_TO_TK)
        {
            return 1;
        }
    return 0;
}

char *
get_token_string(TokenType_t tk)
{
    switch (tk)
        {
        case VOID_TK:
            return "VOID";
        case SEMICOLON_TK:
            return "SEMICOLON";
        case KEYWORD_TK:
            return "KEYWORD";
        case LPAREN_TK:
            return "LPAREN";
        case RPAREN_TK:
            return "RPAREN";
        case LBRACE_TK:
            return "LBRACE";
        case RBRACE_TK:
            return "RBRADE";
        case STRING_TK:
            return "STRING";
        case CONSTANT_TK:
            return "CONSTANT";
        case SPECIAL_TK:
            return "SPECIAL";
        case IDENTIFIER_TK:
            return "IDENTIFIER";
        case LINEFEED_TK:
            return "LINEFEED";
        case ENDOFFILE_TK:
            return "ENDOFFILE";
        case ASSIGNMENT_TK:
            return "ASSIGNMENT";
        case INT_TK:
            return "INT";
        case MAIN_TK:
            return "MAIN";
        case PLUS_TK:
            return "PLUS";
        case MINUS_TK:
            return "MINUS";
        case DIV_TK:
            return "DIV";
        case MULT_TK:
            return "MULT";
        case EQUAL_TK:
            return "EQUAL";
        case EQUAL_TO_TK:
            return "EQUAL TO";
        case COMMA_TK:
            return "COMMA";
        case AND_ADDR_TK:
            return "AND ADDR";
        case AND_TK:
            return "AND";
        case OR_TK:
            return "OR";
        case LT_TK:
            return "LT";
        case LT_EQUAL_TK:
            return "LT EQUAL";
        case GT_TK:
            return "GT";
        case GT_EQUAL_TK:
            return "GT EQUAL";
        case NOT_TK:
            return "NOT";
        case NOT_EQUAL_TK:
            return "NOT EQUAL";
        case RETURN_TK:
            return "RETURN";
        default:
            break;
        }
    return "TOKEN NOT FOUND";
}

Token_t
ctm_token(char * value, size_t line)
{
    Token_t token;
    token.value = malloc(strlen(value) * sizeof(char));
    strcpy(token.value, value);
    token.line = line;
    token.type = ctm_token_typer(token);
    //printf("%zu:%d:\"%s\"\n", line, token.type, value);
    return token;
}


