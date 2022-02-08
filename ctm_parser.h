#ifndef CTM_PARSER_H
#define CTM_PARSER_H

#include "ctm_ast.h"
#include "ctm_scanner.h"

typedef struct parser CtmParser_t;

struct parser
{
  CtmAst_t * ast;
};

void parser (CtmParser_t ** parser, CtmTokenNode_t * head);

void
print_ast(CtmExpList_t * head);

CtmAstNode_t *
parser_parse_id(CtmTokenNode_t ** head);

#endif
