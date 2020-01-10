#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "toolkit.h"

#define MAX_PAD 64

static char pad[MAX_PAD];

char *adddirname(char *path, char *dirnm)
{
/*
NAME
adddirname() - add a dir name to path

SYNOPSIS
  adddirname(char *path, char *dirnm)

DESCRIPTION
  This function adds a dirnm string to path and returns
  a pointer to result kept in internal buffer.

ARGUMENTS
  path - the string to be added
  dirnm - the string containg path

RETURN
  pointer to buffer containing resulting string
  
DEPENDENCIES
  PATHSEP  char constant defined in .h
  stdio   sprintf()

EXAMPLE
  printf("%s\n", addnputs("foo", "bar");

  $ foo/bar
	       
AUTHOR
  Marzvix <marzvix@gmail.com>

CREATED
  qui,  9 de jan de 2020 22:30:19

*/
  strcpy(pad, path);
  if (*(pad+strlen(path)-1) != PATHSEP)
    sprintf(pad, "%s%c%s", path, PATHSEP, dirnm);
  else
    sprintf(pad, "%s%s", path, dirnm);
  return pad;
}

void nputs(char *str)
{
/*
NAME
nputs() - display string in stdout without newline

SYNOPSIS
  nputs(char *str)

DESCRIPTION
  This function displays a string on stdout without
  adding a newline at the end of the string.
  (It is puts() without the newline)

ARGUMENTS
  str - the string to be printed
  return value: void
  
DEPENDENCIES
  stdio   puts()
  string  strlen()
  unistd  write()

EXAMPLE
  nputs("foo");

  $ foo

BUGS
	       
AUTHOR
  Jack Purdum, Que, 1989, C Programmer's Toolkit, pg 252-253
*/

  write(fileno(stdout), str, strlen(str))
    ;
}
