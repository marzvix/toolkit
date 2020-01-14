#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "txtools.h"

static  char buffer[32];

void tst_toupper(void)
{
  puts("Testing toupper...");

  txtupper(buffer, argv[0]);
  puts(buffer);
}

void tst_rand_str(void)
{
  char *pb = buffer;

  puts("Testing toupper...");

  srand(time(NULL));
  rand_str(&pb, rand() % 32);
  printf("[%d]: %s\n",strlen(buffer), buffer);
}

void main(void)
{
  tst_toupper();
  tst_rand_str();
}
