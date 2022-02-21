#include "ctm_scanner.h"
#include "ctm_error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void
push_list(CtmTokenList_t ** list, Token_t t)
{
    CtmTokenNode_t * node = malloc(sizeof(CtmTokenNode_t));
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
output_list(CtmTokenNode_t * head)
{
    if (!head) return;

    printf("%s ", head->token.value);

    output_list(head->next);
}

void
scanner_tokenizer(CtmScanner_t ** scanner, char * value)
{
    push_list(&(*scanner)->list, ctm_token(value, (*scanner)->line));
}

void
scanenr_number(CtmScanner_t ** scanner)
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

    scanner_tokenizer(&(*scanner), value);
}

void
scanenr_alph(CtmScanner_t ** scanner)
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

    scanner_tokenizer(&(*scanner), value);
}

void
scanner_file(CtmScanner_t ** scanner)
{
    (*scanner)->line = 1;
    while (((*scanner)->c = fgetc((*scanner)->fl)) != EOF)
        {

            if (isalpha((*scanner)->c))
                {
                    scanenr_alph(&(*scanner));
                }

            if (isdigit((*scanner)->c))
                {
                    scanenr_number(&(*scanner));
                }

            if ((*scanner)->c == '\t' || (*scanner)->c == ' ') continue;

            switch ((*scanner)->c)
                {
                case '\n':
                    //scanner_tokenizer(&(*scanner), "\n");
                    (*scanner)->line++;
                    break;
                case ',':
                    scanner_tokenizer(&(*scanner), ",");
                    break;
                case '=':
                    scanner_tokenizer(&(*scanner), "=");
                    break;
                case '{':
                    scanner_tokenizer(&(*scanner), "{");
                    break;
                case '}':
                    scanner_tokenizer(&(*scanner), "}");
                    break;
                case '(':
                    scanner_tokenizer(&(*scanner), "(");
                    break;
                case ')':
                    scanner_tokenizer(&(*scanner), ")");
                    break;
                case ';':
                    scanner_tokenizer(&(*scanner), ";");
                    break;
                case '+':
                    scanner_tokenizer(&(*scanner), "+");
                    break;
                case '-':
                    scanner_tokenizer(&(*scanner), "-");
                    break;
                case '*':
                    scanner_tokenizer(&(*scanner), "*");
                    break;
                default:
                    scanner_error((*scanner)->c);
                }
        }
}

