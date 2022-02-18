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

#include <stdio.h>

