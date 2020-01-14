#ifndef _FILETOOLS_H
#define _FILETOOLS_H

/* --- filetools --- */

int create_dir(char *);
int remove_dir(char *);
int isdir(char *);
int isdir(char *);
int isfile(char *);
int exist(char *);

int create_file(char *);
int remove_file(char *);

int getfsize(char *, long *);
  
#endif /* _FILETOOLS_H */
