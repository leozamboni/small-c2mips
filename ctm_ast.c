#include "ctm_ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
add_ast(CtmAst_t ** ast, CtmAstNode_t * node)
{
  CtmExpList_t * new = malloc(sizeof(CtmExpList_t));
  new->ast = node;
  new->next = NULL;
  if (!(*ast)->head)
    {
      (*ast)->head = new;
    }
  if ((*ast)->current)
    {
      (*ast)->current->next = new;
    }
  (*ast)->current = new;
}

CtmAstNode_t *
init_node(Token_t token)
{
  CtmAstNode_t * node = malloc(sizeof(CtmAstNode_t));
  node->dtype = token.type;
  node->value = NULL;
  if (node->dtype == IDENTIFIER_TK || node->dtype == CONSTANT_TK || node->dtype == MAIN_TK)
    {
      node->value = malloc(strlen(token.value) * sizeof(char));
      strcpy(node->value, token.value);
    }
  node->next = NULL;
  return node;
}
