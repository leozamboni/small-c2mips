#ifndef CTM_SYMTAB_H
#define CTM_SYMTAB_H

#include "ctm_token.h"

typedef struct symbol_table CowSymTab_t;

struct symbol_table
{
  TokenType_t id;
  char ch;
  char * str;
};

#endif
