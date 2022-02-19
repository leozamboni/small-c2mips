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
insert_symtab(CtmSymtab_t ** symtab, TokenType_t type, char * ch);

void
print_symtab(CtmSymtab_t * symtab);

_Bool
check_symtab(CtmSymtab_t *, char *);

#endif
