#include "ctm_ast.h"

#include <stdio.h>

void
code_gen_main(CtmAstNode_t * ast, size_t saved_regs)
{
  if (!ast) return;
  code_gen_main(ast->typeP, saved_regs);

  if (ast->type == MAIN && ast->dtype == MAIN_TK)
    {
      printf("main:\n");
    }
  else if (ast->type == ARG && ast->dtype != VOID_TK)
    {
      size_t regI = 0;
      CtmAstNode_t * aux = ast;
      while (aux->type != ARG)
        {
          printf("mov $t%zu, 0\n", regI++);
          if (regI == 7) break;
          aux = aux->next;
        }
    }
  else if (ast->type == ASSIG)
    {
      ast = ast->right;
      printf("li $s%zu, 0\n", saved_regs);
    }
  else if (ast->type == EXP)
    {
      if (ast->dtype == PLUS_TK)
        {
          ast = ast->right;
          printf("addi $s%zu, $s%zu, %s\n", saved_regs, saved_regs, ast->value);
        }
      else
        {
          printf("li $s%zu, %s\n", saved_regs, ast->value);
        }
    }
  else if (ast->type == RET)
    {
      if (ast->dtype == RETURN_TK)
        {
          printf("li $v0, 10\n"\
                 "syscall\n");
        }
    }

  code_gen_main(ast->next, saved_regs);
  code_gen_main(ast->right, saved_regs);
  code_gen_main(ast->left, saved_regs);
}

void
code_gen_gen(CtmExpList_t * head)
{
  size_t saved_regs = 0;
  switch(head->ast->type)
    {
    case MAIN:
      code_gen_main(head->ast, saved_regs);
      break;
    default:
      return;
    }
}

void
code_gen(CtmAst_t * ast)
{
  printf(".text\n" \
         ".globl main\n");
  code_gen_gen(ast->head);
}
