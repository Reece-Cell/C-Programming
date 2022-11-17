#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// a simple parser for this BNF grammar:
// A ::= 0 B
// B ::= 1 A | 2 B | ;

void A(), B();
int count = 0;

// input token
char tok[10];

// return the next token from standard input as a string,
// or return NULL if there is no more input
char *lexan() {
  int n;
  n = scanf("%s", tok);
  if (n == EOF) {
    return NULL;
  }
  return tok;
}

// print an error message and exit
void error(char* msg) {
  printf("%s\n", msg);
  exit(1);
}

// return if the standard input follows the syntax for A,
// else print an error message and exit
void A() {
  char *lookahead;
    //get next token
  lookahead=lexan();
  // the grammar says an expr starts with either "0" or nothing
  if (lookahead == NULL) {
    // error: the input is empty
    error("no");
  } else if (strcmp(lookahead, "0") == 0) {
    // "0" was read
    B();
  } else {
    // an error, because an expr should start with either "0" or nothing
    error("no");
  }
}

// return if the standard input follows the syntax for B,
// else print an error message and exit
void B() { 
  char *lookahead;
    //get next token
  lookahead=lexan();
  // the grammar says an expr is either "1", "2", or ";"
  if (lookahead == NULL) {
    // error: the input is empty
    error("no");
  } else if (strcmp(lookahead, "1") == 0) {
    // "a" was read
    A();
  } else if (strcmp(lookahead, "2") == 0) {
    // "2" was read
    B();
  } else if (strcmp(lookahead, ";") == 0) {
    // ";" was read
    printf("yes");
    exit(1);
  } else {
    // an error, because an expr should start with either "a" or "("
    error("no");
  }
  // hints:
  //   - read the next token
  //   - the next token must be "1" or "2" or ";"
}

int main() {
  A();
  // the input should be one A only
  if (lexan() != NULL) {
    error("no");
  }
  printf("yes\n");
}