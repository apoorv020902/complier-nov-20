#include <stdio.h>
#include "parser.h"
#include "front.h"

static void error();

/* Forward declarations */
void expr_prime();
void term_prime();


/**
 * expr
 * Parses strings in the language generated by the rule:
 * E ::= T E'
 */
void expr() {
    printf("Enter <expr>\n");
    term();
    expr_prime(); // Parse E'
    printf("Exit <expr>\n");
}

/**
 * expr_prime
 * Parses strings in the language generated by the rule:
 * E' ::= + T E' | - T E' | ε
 */
void expr_prime() {
    printf("Enter <expr_prime>\n");
    if (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
        expr_prime(); // Recursively parse E'
    }
    printf("Exit <expr_prime>\n");
}

/**
 * term
 * Parses strings in the language generated by the rule:
 * T ::= F T'
 */
void term() {
    printf("Enter <term>\n");
    factor();
    term_prime(); // Parse T'
    printf("Exit <term>\n");
}

/**
 * term_prime
 * Parses strings in the language generated by the rule:
 * T' ::= * F T' | / F T' | % F T' | ε
 */
void term_prime() {
    printf("Enter <term_prime>\n");
    if (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == MOD_OP) {
        lex();
        factor();
        term_prime(); // Recursively parse T'
    }
    printf("Exit <term_prime>\n");
}

/**
 * factor
 * Parses strings in the language generated by the rule:
 * F ::= (E) | N | V
 */
void factor() {
    printf("Enter <factor>\n");
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex(); // Parse identifier or integer literal
    } else if (nextToken == OPEN_PAREN) {
        lex(); // Consume '('
        expr(); // Parse expression
        if (nextToken == CLOSE_PAREN) {
            lex(); // Consume ')'
        } else {
            error();
        }
    } else {
        error();
    }
    printf("Exit <factor>\n");
}

/**
 * stmt
 * Parses strings in the language generated by the rule:
 * S ::= V = E; | input(V); | output(E); | if (C) {S} else {S}
 */
void stmt() {
    printf("Enter <stmt>\n");
    if (nextToken == IDENT) {
        lex(); // Consume identifier
        if (nextToken == ASSIGN_OP) {
            lex(); // Consume '='
            expr();
            if (nextToken == SEMICOLON) {
                lex(); // Consume ';'
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (nextToken == KEY_IN) {
        lex(); // Consume 'input'
        if (nextToken == OPEN_PAREN) {
            lex();
            if (nextToken == IDENT) {
                lex(); // Consume identifier
                if (nextToken == CLOSE_PAREN) {
                    lex();
                    if (nextToken == SEMICOLON) {
                        lex(); // Consume ';'
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (nextToken == KEY_OUT) {
        lex(); // Consume 'output'
        if (nextToken == OPEN_PAREN) {
            lex();
            expr();
            if (nextToken == CLOSE_PAREN) {
                lex();
                if (nextToken == SEMICOLON) {
                    lex();
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    } else if (nextToken == KEY_IF) {
        lex(); // Consume 'if'
        if (nextToken == OPEN_PAREN) {
            lex(); // Consume '('
            cond(); // Parse condition
            if (nextToken == CLOSE_PAREN) {
                lex(); // Consume ')'
                if (nextToken == OPEN_CURL) {
                    lex(); // Consume '{'
                    stmt(); // Parse statement
                    if (nextToken == CLOSE_CURL) {
                        lex(); // Consume '}'
                        if (nextToken == KEY_ELSE) {
                            lex(); // Consume 'else'
                            if (nextToken == OPEN_CURL) {
                                lex(); // Consume '{'
                                stmt(); // Parse statement
                                if (nextToken != CLOSE_CURL) {
                                    error();
                                } else {
                                    lex(); // Consume '}'
                                }
                            } else {
                                error();
                            }
                        }
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    } else {
        error();
    }
    printf("Exit <stmt>\n");
}

/**
 * cond
 * Parses strings in the language generated by the rule:
 * C ::= E < E | E > E | E == E | E != E | E <= E | E >= E
 */
void cond() {
    printf("Enter <cond>\n");
    expr();
    if (nextToken == LESSER_OP || nextToken == GREATER_OP || 
        nextToken == EQUAL_OP || nextToken == NEQUAL_OP || 
        nextToken == LEQUAL_OP || nextToken == GEQUAL_OP) {
        lex(); // Consume comparison operator
        expr();
    } else {
        error();
    }
    printf("Exit <cond>\n");
}

/**
 * error
 * Prints an error message.
 */
static void error() {
    printf("Syntax Error: Unexpected token %s\\n", tokenCodeToName(nextToken));
}
