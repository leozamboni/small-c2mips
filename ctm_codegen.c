#include "ctm_ast.h"

#include <stdio.h>

void
code_gen_main(CtmAstNode_t * ast)
{
  if (!ast) return;
  code_gen_main(ast->left);

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
  else if (ast->type == RET)
    {
      if (ast->dtype == RETURN_TK)
        {
          printf("li $v0, 10\n"\
                 "syscall\n");
        }
    }

  code_gen_main(ast->right);
  code_gen_main(ast->next);
}

void
code_gen_gen(CtmExpList_t * head)
{
  switch(head->ast->type)
    {
    case MAIN:
      code_gen_main(head->ast);
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
