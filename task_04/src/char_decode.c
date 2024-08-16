#include <math.h>
#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_ARGS 3

#define ENCODE_MODE 0
#define DECODE_MODE 1

int getdigit(char c) {
  int n = -1;
  if (c >= '0' && c <= '9')
    n = c - '0';
  else if (c >= 'A' && c <= 'F')
    n = c - 'A' + 10;
  else
    n = -1;
  return n;
}

char getdigitchar(int c) {
  char n = '\0';
  if (c >= 0 && c <= 9)
    n = c + '0';
  else if (c >= 10 && c <= 15)
    n = c - 10 + 'A';
  else
    n = '\0';
  return n;
}

void printASCIICode(char c) {
  int n1 = (c / 16);
  int n2 = (c % 16);

  char c1 = getdigitchar(n1);
  char c2 = getdigitchar(n2);
  printf("%c%c", c1, c2);
}

int decode() {
  char c1, c2;
  int n1, n2;

  while ((n1 = getdigit(c1 = getchar())) != -1 &&
         (n2 = getdigit(c2 = getchar())) != -1) {
    char res = n1 * 16 + n2;

    // read sapce
    c1 = getchar();
    if (c1 != ' ' && c1 != '\n') return ERR_IO;

    printf("%c", res);
    if (c1 == '\n')
      return OK;
    else
      printf(" ");
  }
  return ERR_IO;
}

int encode() {
  char c1;

  while ((c1 = getchar()) != '\n') {
    char c2 = c1;
    // read sapce
    c1 = getchar();
    if (c1 != ' ' && c1 != '\n') return ERR_IO;
    printASCIICode(c2);
    if (c1 == '\n')
      return OK;
    else
      printf(" ");
  }
  return OK;
  ;
}
int main(int n, char **args) {
  if (n != 2) {
    printf("args/a");
    return ERR_ARGS;
  }
  int mode;
  if (sscanf(args[1], "%d", &mode) != 1) {
    printf("IOn/a");
    return ERR_IO;
  }
  if (mode != ENCODE_MODE && mode != DECODE_MODE) {
    printf("n/a");
    return ERR_RANGE;
  }

  if (mode == DECODE_MODE) {
    int rc = decode();
    if (rc != OK) {
      printf("n/a");
    }
    return rc;
  } else if (mode == ENCODE_MODE) {
    int rc = encode();
    if (rc != OK) {
      printf("n/a");
    }
    return rc;
  }

  return OK;
}