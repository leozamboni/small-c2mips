#include "ctm.h"

#include <stdio.h>
#include <stdlib.h>

void
ctm(FILE * fl)
{
  Ctm_t * ctm;
  create(&ctm);
  ctm->scanner->fl = fl;

  compiler(&ctm);
}

void
create(Ctm_t ** ctm)
{
  (*ctm) = malloc(sizeof(Ctm_t));
  (*ctm)->scanner = malloc(sizeof(CtmScanner_t));
  (*ctm)->scanner->list = malloc(sizeof(CtmTokenList_t));
  (*ctm)->scanner->list->head = NULL;
  (*ctm)->scanner->list->current = NULL;
  (*ctm)->parser = malloc(sizeof(CtmParser_t));
  (*ctm)->parser->ast = malloc(sizeof(CtmAst_t));
  (*ctm)->parser->ast->current = NULL;
  (*ctm)->parser->ast->head = NULL;
}

void
compiler(Ctm_t ** ctm)
{
  scanner_file(&(*ctm)->scanner);
  //output_list((*ctm)->scanner->list->head);
  parser(&(*ctm)->parser, (*ctm)->scanner->list->head);
  //print_ast((*ctm)->parser->ast->head);
  code_gen((*ctm)->parser->ast);
}
