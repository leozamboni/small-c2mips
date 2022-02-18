#ifndef CTM_SYMTAB_H
#define CTM_SYMTAB_H

#include "ctm_token.h"

typedef struct symbol_table CtmSymtab_t;

struct symbol_table
{
  TokenType_t type;
  char * str;
  CtmSymtab_t * next;
};


void
insert_symtab(CtmSymtab_t **, TokenType_t, char *);


#endif
