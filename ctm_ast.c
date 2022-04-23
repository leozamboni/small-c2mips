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
