#ifndef CTM_SCANNER_H
#define CTM_SCANNER_H

#include "ctm_token.h"

#include <stdio.h>

typedef struct ctm_token_node CowTokenNode_t;

struct ctm_token_node
{
  CowTokenNode_t * next;
  Token_t token;
  CowTokenNode_t * prior;
};

typedef struct ctm_token_list CowTokenList_t;

struct ctm_token_list
{
  CowTokenNode_t * head;
  CowTokenNode_t * current;
};

typedef struct ctm_scanner CowScanner_t;

struct ctm_scanner
{
  CowTokenList_t * list;
  FILE * fl;
  int c;
  size_t line;
};

void ctm_scanner_file(CowScanner_t ** scanner);

void output_list(CowTokenNode_t * head);

#endif
