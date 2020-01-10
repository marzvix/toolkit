#include <stdio.h>
#include "txtools.h"

int main(int argc, char **argv)
{
  char pad[33];
  int i;
  
  puts("Testing toupper...");
  for(i=0; i < argc; i++) {
    txtupper(pad, argv[i]);
    puts(pad);
  }
  
  return 0;
}
