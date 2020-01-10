#include <stdio.h>
#include <stdlib.h>
#include "filetools.h"

int main(int argc, char *argv[])
{
  int status;
  long size;

  status = create_dir(argv[argc-1]);
  if (status == EXIT_SUCCESS)
      printf("dir created: %s\n", argv[argc-1]);
  else
    perror(argv[argc-1]);
    
  if (status == EXIT_SUCCESS)
    printf("%s is %sdir!\n", argv[argc-1],
	   isdir(argv[argc-1]) ?"":"not ");
  else
    perror(argv[argc-1]);
  
  status = remove_dir(argv[argc-1]);
  if (status == EXIT_SUCCESS)
      printf("dir removed: %s\n", argv[argc-1]);
  else
    perror(argv[argc-1]);

  if (status == EXIT_SUCCESS)
    printf("%s %sexist!""\n", argv[argc-1],
	   isdir(argv[argc-1]) ?"":"not ");
  else
    perror(argv[argc-1]);
 
  status = create_file(argv[argc-1]);
  if (status == EXIT_SUCCESS)
      printf("file created: %s\n", argv[argc-1]);
  else
    perror(argv[argc-1]);
    
  status = remove_file(argv[argc-1]);
  if (status == EXIT_SUCCESS)
      printf("file removed: %s\n", argv[argc-1]);
  else
    perror(argv[argc-1]);
    
  status = getfsize(argv[argc-1], &size);
  if (status == EXIT_SUCCESS)
      printf("%s size: %ld\n", argv[argc-1], size);
  else
    perror(argv[argc-1]);

  exit(status);
}
