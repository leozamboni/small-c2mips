#ifndef CTM_H
#define CTM_H
#include <stdio.h>
#include "ctm_symtab.h"
#include "ctm_codegen.h"
#include "ctm_scanner.h"
#include "ctm_parser.h"
typedef struct ctm Ctm_t;

struct ctm
{
  CtmScanner_t * scanner;
  CtmSymtab_t * symtab;
  CtmParser_t * parser;
};

void ctm(FILE *);

void create(Ctm_t **);

void compiler(Ctm_t **);

#endif
