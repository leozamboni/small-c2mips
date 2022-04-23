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
#include "ctm_semantic.h"

void
semantic_register(CtmSymtab_t * symtab, size_t regs)
{
    if (!symtab) return;
    symtab->reg = regs++;
    semantic_register(symtab->next, regs);
}

void
semantic(CtmSymtab_t * symtab, CtmAst_t * ast)
{
    semantic_register(symtab, 0);
    //semantic_analysis(CtmSymtab_t * symtab, CtmAstNode_t * ast);
}