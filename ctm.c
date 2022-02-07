#include "ctm.h"

#include <stdio.h>
#include <stdlib.h>

void
ctm(FILE * fl)
{
  Cow_t * ctm;
  create(&ctm);
  ctm->scanner->fl = fl;

  compiler(&ctm);
}

void
create(Cow_t ** ctm)
{
  (*ctm) = malloc(sizeof(Cow_t));
  (*ctm)->scanner = malloc(sizeof(CowScanner_t));
  (*ctm)->scanner->list = malloc(sizeof(CowTokenList_t));
  (*ctm)->scanner->list->head = NULL;
  (*ctm)->scanner->list->current = NULL;
  (*ctm)->parser = malloc(sizeof(CowParser_t));
  (*ctm)->parser->ast = malloc(sizeof(CowAst_t));
  (*ctm)->parser->ast->current = NULL;
  (*ctm)->parser->ast->head = NULL;
}

void
compiler(Cow_t ** ctm)
{
  ctm_scanner_file(&(*ctm)->scanner);
  output_list((*ctm)->scanner->list->head);
  parser(&(*ctm)->parser, (*ctm)->scanner->list->head);
  puts("");
  print_ast((*ctm)->parser->ast->head);
}
