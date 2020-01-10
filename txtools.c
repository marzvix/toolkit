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
