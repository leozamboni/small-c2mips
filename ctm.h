#ifndef CTM_H
#define CTM_H
#include <stdio.h>
#include "ctm_scanner.h"
#include "ctm_parser.h"
typedef struct ctm Cow_t;

struct ctm
{
  CowScanner_t * scanner;
  CowParser_t * parser;
};

void ctm(FILE * fl);

void create(Cow_t ** ctm);

void compiler(Cow_t ** ctm);

#endif
