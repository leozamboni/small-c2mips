#ifndef CTM_AST_H
#define CTM_AST_H

#include "ctm_token.h"

typedef struct ctm_ast_node CtmAstNode_t;

struct ctm_ast_node
{
  enum
  {
    EXP,
    CALL,
    ARG,
    RET,
    ASSIG,
    MAIN,
    FUNC,
  } type;
  char * value;
  TokenType_t dtype;
  CtmAstNode_t * next;
  CtmAstNode_t * left;
  CtmAstNode_t * right;
};

typedef struct ctm_exp_list CtmExpList_t;

struct ctm_exp_list
{
  CtmAstNode_t * ast;
  CtmExpList_t * next;
};

typedef struct ctm_ast CtmAst_t;

struct ctm_ast
{
  CtmExpList_t * head;
  CtmExpList_t * current;
};

void
add_ast(CtmAst_t ** ast, CtmAstNode_t * node);

CtmAstNode_t *
init_node(Token_t token);

#endif
