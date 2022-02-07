#ifndef CTM_AST_H
#define CTM_AST_H

#include "ctm_token.h"

typedef struct ctm_ast_node CowAstNode_t;

struct ctm_ast_node
{
	enum {
		EXP,
		CALL,
		ARG, 
		RET,
		ASSIG,
		FUNC,
	}type;
  char * value;
  TokenType_t dtype;
  CowAstNode_t * next;
  CowAstNode_t * left;
  CowAstNode_t * right;
};

typedef struct ctm_exp_list CowExpList_t;

struct ctm_exp_list
{
  CowAstNode_t * ast;
  CowExpList_t * next;
};

typedef struct ctm_ast CowAst_t;

struct ctm_ast
{
  CowExpList_t * head;
  CowExpList_t * current;
};

void
add_ast(CowAst_t ** ast, CowAstNode_t * node);

CowAstNode_t *
init_node(Token_t token);

#endif
