#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "toolkit.h"

int main(int argc, char *argv[])
{
  int i=0;

  puts("Testing adddirname...");

  nputs(adddirname((argc>1) ? argv[1] : "./", "ttt"));

  puts("Testing nputs...");

  for(i=0; i < argc; i++) {
    nputs(argv[i]); nputs(" ");
  }
  exit(0);
}
