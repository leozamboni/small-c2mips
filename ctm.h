/*  CTM - C TO MIPS
 *  Copyright (c) 2022 Leonardo Z. Nunes
 *
 *  this program is free software: you can redistribute it and/or modify
 *  it under the terms of the gnu general public license as published by
 *  the free software foundation, either version 3 of the license, or
 *  (at your option) any later version.
 *
 *  this program is distributed in the hope that it will be useful,
 *  but without any warranty; without even the implied warranty of
 *  merchantability or fitness for a particular purpose.  see the
 *  gnu general public license for more details.
 *
 *  you should have received a copy of the gnu general public license
 *  along with this program.  if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CTM_H
#define CTM_H

#include "ctm_symtab.h"
#include "ctm_codegen.h"
#include "ctm_scanner.h"
#include "ctm_parser.h"
#include "ctm_semantic.h"

#include <stdio.h>

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
