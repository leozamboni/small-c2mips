#include "ctm_ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
add_ast(CowAst_t ** ast, CowAstNode_t * node)
{
  CowExpList_t * new = malloc(sizeof(CowExpList_t));
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

CowAstNode_t *
init_node(Token_t token)
{
  CowAstNode_t * node = malloc(sizeof(CowAstNode_t));
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
