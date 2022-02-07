#include <stdio.h>
#include <stdlib.h>

#include "ctm.h"

int
main(int argc, const char ** argv)
{
  FILE *fl = fopen(argv[1], "r");
  if (!fl) exit(EXIT_FAILURE);

  ctm(fl);

  return 0;
}
