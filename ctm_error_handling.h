#ifndef CTM_ERROR_HANDLING_H
#define CTM_ERROR_HANDLING_H

#include "ctm_token.h"

void
ctm_parser_error(Token_t token);

void
ctm_scanner_error(int c);

#endif
