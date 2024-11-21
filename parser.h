#ifndef PARSER_H
#define PARSER_H

void expr();
void expr_prime();
void term();
void term_prime();
void factor();
void stmt();
void cond();

extern int nextToken;

#endif
