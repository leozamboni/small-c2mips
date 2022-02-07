#ifndef CTM_PARSER_H
#define CTM_PARSER_H

#include "ctm_ast.h"
#include "ctm_scanner.h"

typedef struct parser CowParser_t;

struct parser
{
  CowAst_t * ast;
};

void parser (CowParser_t ** parser, CowTokenNode_t * head);

void
print_ast(CowExpList_t * head);


#endif
