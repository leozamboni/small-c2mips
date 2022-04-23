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
    (*ctm)->symtab = NULL;
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
    parser(&(*ctm)->parser, (*ctm)->scanner->list->head, &(*ctm)->symtab);
    //print_symtab((*ctm)->symtab);
    //print_ast((*ctm)->parser->ast->head);
    semantic((*ctm)->symtab, (*ctm)->parser->ast);
    code_gen((*ctm)->parser->ast, (*ctm)->symtab);
}
