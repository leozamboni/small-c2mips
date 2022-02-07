#ifndef CTM_SCANNER_H
#define CTM_SCANNER_H

#include "ctm_token.h"

#include <stdio.h>

typedef struct ctm_token_node CtmTokenNode_t;

struct ctm_token_node
{
  CtmTokenNode_t * next;
  Token_t token;
  CtmTokenNode_t * prior;
};

typedef struct ctm_token_list CtmTokenList_t;

struct ctm_token_list
{
  CtmTokenNode_t * head;
  CtmTokenNode_t * current;
};

typedef struct ctm_scanner CtmScanner_t;

struct ctm_scanner
{
  CtmTokenList_t * list;
  FILE * fl;
  int c;
  size_t line;
};

void scanner_file(CtmScanner_t ** scanner);

void output_list(CtmTokenNode_t * head);

#endif
