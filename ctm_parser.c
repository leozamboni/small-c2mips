#include "ctm_scanner.h"
#include "ctm_parser.h"
#include "ctm_symtab.h"
#include "ctm_error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
list_eat(CtmTokenNode_t ** node, TokenType_t type)
{
  if ((*node)->token.type != type)
    {
      parser_error((*node)->token);
    }
  (*node) = (*node)->next;
}

CtmAstNode_t *
parser_parse_exp(CtmTokenNode_t ** head)
{
  if ((*head)->token.type == SEMICOLON_TK) return NULL;

  CtmAstNode_t * node = init_node((*head)->token);
  node->type = EXP;

  if ((*head)->prior->token.type == EQUAL_TK)
    {
      if ((*head)->token.type == RPAREN_TK)
        {
          while ((*head)->token.type != LPAREN_TK)
            {
              if ((*head)->token.type == SEMICOLON_TK)
                {
                  parser_error((*head)->token);
                }
              if ((*head)->prior->token.type == RPAREN_TK || is_operator((*head)->prior->token.type))
                {
                  list_eat(&(*head), (*head)->token.type == IDENTIFIER_TK ? IDENTIFIER_TK : CONSTANT_TK);
                }
              if ((*head)->prior->token.type == CONSTANT_TK || (*head)->prior->token.type == IDENTIFIER_TK)
                {
                  if (!is_operator((*head)->token.type))
                    {
                      parser_error((*head)->token);
                    }
                  list_eat(&(*head), (*head)->token.type);
                }
            }
          list_eat(&(*head), LPAREN_TK);
        }
      else
        {
          list_eat(&(*head), (*head)->token.type == IDENTIFIER_TK ? IDENTIFIER_TK : CONSTANT_TK);
        }
    }
  else if ((*head)->prior->token.type == LPAREN_TK)
    {
      if (!is_operator((*head)->token.type))
        {
          parser_error((*head)->token);
        }
      list_eat(&(*head), (*head)->token.type);
    }
  else if (is_operator((*head)->prior->token.type))
    {
      list_eat(&(*head), (*head)->token.type == IDENTIFIER_TK ? IDENTIFIER_TK : CONSTANT_TK);
    }
  else if ((*head)->prior->token.type == CONSTANT_TK || (*head)->prior->token.type == IDENTIFIER_TK)
    {
      if (!is_operator((*head)->token.type))
        {
          parser_error((*head)->token);
        }
      list_eat(&(*head), (*head)->token.type);
    }
  else
    {
      list_eat(&(*head), (*head)->token.type == IDENTIFIER_TK ? IDENTIFIER_TK : CONSTANT_TK);
    }

  node->right = parser_parse_exp(&(*head));

  return node;
}

CtmAstNode_t *
parser_parse_return(CtmTokenNode_t ** head)
{
  CtmAstNode_t * node = init_node((*head)->token);
  node->type = RET;

  list_eat(&(*head), RETURN_TK);

  node->right = parser_parse_exp(&(*head));

  return node;
}

CtmAstNode_t *
parser_parse_arg(CtmTokenNode_t ** head)
{
  if ((*head)->token.type == LPAREN_TK) return NULL;

  CtmAstNode_t * node = init_node((*head)->token);
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
        parser_error((*head)->prior->token);
    }
  else
    {
      parser_error((*head)->token);
    }

  node->next = parser_parse_arg(&(*head));

  return node;
}

CtmAstNode_t *
parser_parse_block(CtmTokenNode_t ** head)
{
  if ((*head)->token.type == LBRACE_TK) return NULL;

  CtmAstNode_t * node = NULL;
  node = malloc(sizeof(CtmAstNode_t));

  if (is_dtype((*head)->token.type))
    {
      list_eat(&(*head), (*head)->token.type);
    }

  switch ((*head)->token.type)
    {
    case RETURN_TK:
      node = parser_parse_return(&(*head));
      break;
    case IDENTIFIER_TK:
      node = parser_parse_id(&(*head));
      break;
    default:
      list_eat(&(*head), (*head)->token.type);
      break;
    }

  node->left = parser_parse_block(&(*head));

  return node;
}

CtmAstNode_t *
parser_parse_id(CtmTokenNode_t ** head)
{
  CtmAstNode_t * node = init_node((*head)->token);
  node->typeP = init_node((*head)->prior->token);

//  insert_symtab(&symtab, (*head)->token.type, (*head)->token.value);

  list_eat(&(*head), (*head)->token.type == MAIN_TK ? MAIN_TK : IDENTIFIER_TK);

  if ((*head)->token.type == RPAREN_TK)
    {
      node->type = (*head)->prior->token.type == MAIN_TK ? MAIN : CALL;

      list_eat(&(*head), RPAREN_TK);

      node->next = parser_parse_arg(&(*head));

      list_eat(&(*head), LPAREN_TK);
      list_eat(&(*head), RBRACE_TK);

      node->right = parser_parse_block(&(*head));

      list_eat(&(*head), LBRACE_TK);
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
      parser_error((*head)->token);
    }

  return node;
}

void
parser (CtmParser_t ** parser, CtmTokenNode_t * head)
{
  add_ast(&(*parser)->ast, parser_parse_id(&head->next));
}

void
print_ast_node(CtmAstNode_t * ast)
{
  if (!ast) return;
  print_ast_node(ast->typeP);
  if (ast->value) printf("%s\n", ast->value);
  else printf("%s\n", get_token_string(ast->dtype));
  print_ast_node(ast->next);
  print_ast_node(ast->right);
  print_ast_node(ast->left);
}

void
print_ast(CtmExpList_t * head)
{
  if (!head) return;
  print_ast_node(head->ast);
  print_ast(head->next);
}
