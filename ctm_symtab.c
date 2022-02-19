#include "ctm_symtab.h"
#include "ctm_token.h"

#include <stdlib.h>
#include <string.h>

void
insert_symtab(CtmSymtab_t ** symtab, TokenType_t type, char * str)
{
  CtmSymtab_t * new = malloc(sizeof(CtmSymtab_t));
  new->str = malloc(strlen(str) * sizeof(char));
  strcpy(new->str, str);
  new->next = NULL;
  new->type = type;
  if (!(*symtab)->next)
    {
      new->next = (*symtab);
    }
  (*symtab) = new;
}

_Bool
check_symtab(CtmSymtab_t * symtab, char * value)
{
  if (!symtab) return 0;
  if (strcmp(symtab->str, value) == 0) return 1;
  return check_symtab(symtab->next, value);
}

void
print_symtab(CtmSymtab_t * symtab)
{
  if (!symtab) return;
  printf("%d: %s\n", symtab->type, symtab->str);
  print_symtab(symtab->next);
}


#include <stdio.h>

