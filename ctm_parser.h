#ifndef CTM_PARSER_H
#define CTM_PARSER_H

#include "ctm_ast.h"
#include "ctm_symtab.h"
#include "ctm_scanner.h"

typedef struct parser CtmParser_t;

struct parser
{
    CtmAst_t * ast;
};

void
parser (CtmParser_t **, CtmTokenNode_t *, CtmSymtab_t **);

void
print_ast(CtmExpList_t *);

CtmAstNode_t *
parser_parse_id(CtmTokenNode_t **, CtmSymtab_t **);

#endif
