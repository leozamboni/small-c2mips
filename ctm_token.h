#ifndef CTM_TOKEN_H
#define CTM_TOKEN_H

#include <stdio.h>

enum token_type
{
  VOID_TK,
  SEMICOLON_TK,
  KEYWORD_TK,
  LPAREN_TK,
  RPAREN_TK,
  LBRACE_TK,
  RBRACE_TK,
  STRING_TK,
  CONSTANT_TK,
  SPECIAL_TK,
  IDENTIFIER_TK,
  LINEFEED_TK,
  ENDOFFILE_TK,
  ASSIGNMENT_TK,
  INT_TK,
  MAIN_TK,
  PLUS_TK,
  MINUS_TK,
  DIV_TK,
  MUL_TK,
  EQUAL_TK,
  COMMA_TK,
  AND_TK,
  OR_TK,
  LT_TK,
  BT_TK,
  NOT_TK,
  RETURN_TK,
};

typedef enum token_type TokenType_t;

typedef struct token Token_t;

struct token
{
  char * value;
  size_t line;
  TokenType_t type;
};

Token_t ctm_token(char * value, size_t line);

char * get_token_string(TokenType_t tk);

_Bool
is_dtype(TokenType_t tk);

#endif
