#include "ctm_scanner.h"
#include "ctm_error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
push_list(CowTokenList_t ** list, Token_t t)
{
  CowTokenNode_t * node = malloc(sizeof(CowTokenNode_t));
  node->token = t;
  node->next = NULL;
  node->prior = (*list)->current;
  if ((*list)->current)
    {
      (*list)->current->next = node;
    }
  if (!(*list)->head)
    {
      (*list)->head = node;
    }
  (*list)->current = node;
}

void
output_list(CowTokenNode_t * head)
{
  if (!head) return;

  printf("%s ", head->token.value);

  output_list(head->next);
}

void
ctm_scanner_tokenizer(CowScanner_t ** scanner, char * value)
{
  push_list(&(*scanner)->list, ctm_token(value, (*scanner)->line));
}

void
ctm_scanenr_number(CowScanner_t ** scanner)
{

  char * value = calloc(1, sizeof(char));
  do
    {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, (char[])
      {
        (*scanner)->c, 0
      });
      (*scanner)->c = fgetc((*scanner)->fl);
    }
  while (isdigit((*scanner)->c));

  ctm_scanner_tokenizer(&(*scanner), value);
}

void
ctm_scanenr_alph(CowScanner_t ** scanner)
{
  char * value = calloc(1, sizeof(char));
  do
    {
      value = realloc(value, (strlen(value) + 2) * sizeof(char));
      strcat(value, (char[])
      {
        (*scanner)->c, 0
      });
      (*scanner)->c = fgetc((*scanner)->fl);
    }
  while (isalpha((*scanner)->c));

  ctm_scanner_tokenizer(&(*scanner), value);
}

void
ctm_scanner_file(CowScanner_t ** scanner)
{
  (*scanner)->line = 1;
  while (((*scanner)->c = fgetc((*scanner)->fl)) != EOF)
    {

      if (isalpha((*scanner)->c))
        {
          ctm_scanenr_alph(&(*scanner));
        }

      if (isdigit((*scanner)->c))
        {
          ctm_scanenr_number(&(*scanner));
        }

      if ((*scanner)->c == '\t' || (*scanner)->c == ' ') continue;

      switch ((*scanner)->c)
        {
        case '\n':
          ctm_scanner_tokenizer(&(*scanner), "\n");
          (*scanner)->line++;
          break;
        case ',':
          ctm_scanner_tokenizer(&(*scanner), ",");
          break;
        case '{':
          ctm_scanner_tokenizer(&(*scanner), "{");
          break;
        case '}':
          ctm_scanner_tokenizer(&(*scanner), "}");
          break;
        case '(':
          ctm_scanner_tokenizer(&(*scanner), "(");
          break;
        case ')':
          ctm_scanner_tokenizer(&(*scanner), ")");
          break;
        case ';':
          ctm_scanner_tokenizer(&(*scanner), ";");
          break;
        default:
          ctm_scanner_error((*scanner)->c);
        }
    }
}

