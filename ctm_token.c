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
    case '=':
      return EQUAL_TK;
    case '/':
      return DIV_TK;
    case '*':
      return MUL_TK;
    case '&':
      return AND_TK;
    case '|':
      return OR_TK;
    case '!':
      return NOT_TK;
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

char *
get_token_string(TokenType_t tk)
{
  switch (tk)
    {
    case RETURN_TK:
      return "RETURN";
    case VOID_TK:
      return "VOID";
    case INT_TK:
      return "INT";
    case STRING_TK:
      return "STRING";
    default:
      break;
    }
  return NULL;
}

Token_t
ctm_token(char * value, size_t line)
{
  Token_t token;
  token.value = malloc(strlen(value) * sizeof(char));
  strcpy(token.value, value);
  token.line = line;
  token.type = ctm_token_typer(token);
// printf("%zu:%d:\"%s\"\n", line, token.type, value);
  return token;
}


