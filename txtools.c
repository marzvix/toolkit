#include <stdlib.h>
#include <time.h>
#include <ctype.h>

/* -- convert a text string to upper case -- */
void txtupper(char *c2, char *c1)
{
  while (*c1) {
    *c2 = toupper(*c1);
    c1++;
    c2++;
  }
  *c2 = '\0';
}

/* -- generate a random string with 
      variable size 0~max and filled with
      ascii codes 32~126 
      A srand(time(NULL)) comand have to
      be previous executed    -- */
void rand_str( char **s, size_t count )
{
  while (count--)
    *((*s)++) = ' ' + (rand() % 94);
}

/* -- skip over white spaces -- */
#define iswhite(c) ( (c) == ' ' || (c) == '\t' ) 
void skip_white(char **s)
{
  while(iswhite(**s))
    (*s)++;
}

