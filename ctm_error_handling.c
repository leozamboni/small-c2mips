#include "ctm_error_handling.h"

#include <stdio.h>
#include <stdlib.h>

void
ctm_parser_error(Token_t token)
{
  fprintf(stderr, "parser: `%s` unexpected value\n", token.value);
  exit(EXIT_FAILURE);
}

void
ctm_scanner_error(int c)
{
  fprintf(stderr, "scanner: `%c` unexpected value\n", c);
  exit(EXIT_FAILURE);
}
