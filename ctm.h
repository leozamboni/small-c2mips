#ifndef CTM_H
#define CTM_H
#include <stdio.h>
#include "ctm_codegen.h"
#include "ctm_scanner.h"
#include "ctm_parser.h"
typedef struct ctm Ctm_t;

struct ctm
{
  CtmScanner_t * scanner;
  CtmParser_t * parser;
};

void ctm(FILE * fl);

void create(Ctm_t ** ctm);

void compiler(Ctm_t ** ctm);

#endif
