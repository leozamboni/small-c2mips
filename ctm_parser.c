#include "ctm_scanner.h"
#include "ctm_parser.h"
#include "ctm_error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
list_eat(CowTokenNode_t ** node, TokenType_t type)
{
  if ((*node)->token.type != type)
    {
      ctm_parser_error((*node)->token);
    }
  (*node) = (*node)->next;
}

CowAstNode_t *
parser_parse_exp(CowTokenNode_t ** head)
{
  if ((*head)->token.type == SEMICOLON_TK) return NULL;

  CowAstNode_t * node = init_node((*head)->token);
	node->type = EXP;

  list_eat(&(*head), (*head)->token.type);

  node->right = parser_parse_exp(&(*head));

  return node;
}

CowAstNode_t *
parser_parse_return(CowTokenNode_t ** head)
{
  CowAstNode_t * node = init_node((*head)->token);
	node->type = RET;

  list_eat(&(*head), RETURN_TK);

  node->right = parser_parse_exp(&(*head));

  return node;
}

CowAstNode_t *
parser_parse_arg(CowTokenNode_t ** head)
{
  if ((*head)->token.type == LPAREN_TK) return NULL;

  CowAstNode_t * node = init_node((*head)->token);
  node->type = ARG;

  if (is_dtype((*head)->prior->token.type))
    {
      list_eat(&(*head), IDENTIFIER_TK);
      if ((*head)->token.type != LPAREN_TK)
        list_eat(&(*head), COMMA_TK);
    }
  else if (is_dtype((*head)->token.type))
    {
      list_eat(&(*head), (*head)->token.type);
      if ((*head)->token.type == LPAREN_TK && (*head)->prior->token.type != VOID_TK)
        ctm_parser_error((*head)->prior->token);
    }
  else
    {
      ctm_parser_error((*head)->token);
    }

  node->next = parser_parse_arg(&(*head));

  return node;
}

CowAstNode_t *
parser_parse_block(CowTokenNode_t ** head)
{
  if ((*head)->token.type == LBRACE_TK) return NULL;

  CowAstNode_t * node = NULL;
  node = malloc(sizeof(CowAstNode_t));

  if ((*head)->token.type == LINEFEED_TK)
    {
      list_eat(&(*head), LINEFEED_TK);
    }

  switch ((*head)->token.type)
    {
    case RETURN_TK:
      node = parser_parse_return(&(*head));
      break;
    default:
      ctm_parser_error((*head)->token);
    }

  list_eat(&(*head), (*head)->token.type);

  node->left = parser_parse_block(&(*head)->next);

  return node;
}

CowAstNode_t *
parser_parse_id(CowTokenNode_t ** head)
{
  CowAstNode_t * node = init_node((*head)->token);
  node->left = init_node((*head)->prior->token);

  if ((*head)->token.type == MAIN_TK)
    {
      (*head)->token.type = IDENTIFIER_TK;
    }

  list_eat(&(*head), IDENTIFIER_TK);

  if ((*head)->token.type == RPAREN_TK)
    {
			node->type = FUNC;

      list_eat(&(*head), RPAREN_TK);

      node->next = parser_parse_arg(&(*head));

      list_eat(&(*head), LPAREN_TK);
      list_eat(&(*head), RBRACE_TK);

      node->right = parser_parse_block(&(*head));
    }
  else if ((*head)->token.type == EQUAL_TK)
    {
		  node->type = ASSIG;

      list_eat(&(*head), EQUAL_TK);

      node->right = parser_parse_exp(&(*head));

      list_eat(&(*head), SEMICOLON_TK);
    }
  else
    {
      ctm_parser_error((*head)->token);
    }

  return node;
}

void
parser (CowParser_t ** parser, CowTokenNode_t * head)
{
  add_ast(&(*parser)->ast, parser_parse_id(&head->next));
}

void
print_ast_node(CowAstNode_t * ast)
{
  if (!ast) return;
  print_ast_node(ast->left);
  if (ast->value) printf("%s\n", ast->value);
  else printf("%s\n", get_token_string(ast->dtype));
  print_ast_node(ast->next);
  print_ast_node(ast->right);
}

void
print_ast(CowExpList_t * head)
{
  if (!head) return;
  print_ast_node(head->ast);
  print_ast(head->next);
}
