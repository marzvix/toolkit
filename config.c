#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define MAX_PAD 64

static FILE *fp;
static char pad[MAX_PAD];
static int status;
struct tm tm = *localtime(&t);
static time_t t = time(NULL);

void create_config(char *progname)
{
  /* NAME
       config

     SYNOPSIS
       configure program parameters description: config is 
       to be called immediatelly after program starts. 

       It divided in 4 phases

       phase 1     
       If ~/.config dir exists, create a new one

       phase 2
       If ~/.config/app dir do not exists, create 
       a new one

       phase 3
       if ~/.config/app/app.conf file, create a 
       new one to keep default parameters and
       insert initial ones

       phase 4	  
       If ~/.config/app.conf exists, load their
       parameters

    DEPENDENCIES
      stdio

    BUGS
      - no switches or dialogs to select options
      - hardcoded parameters
      - if there is another app with same name using
        config dir, it will clash
      - buffer is limmited to 64 chars
      - parameters are isolated variables (not a struct)
        created: seg,  6 de jan de 2020 10:11:06
  */

  /* -- phase 1 - config dirs creations */

  /* -- ~/.config - just in case it not exist */
  strcpy(pad, getenv("HOME"));
  strcat(pad, "/");
  strcat(pad, ".config_");
  
  status = create_dir(pad);

  if (status == -1) /* couldn't be created */
    return;

  /* - app dir cration - */
  strcat(pad, "/");
  strcat(pad, progname);

  status = create_dir(pad); 

  if (status == -1) 
    return;

  status = create_dir(pad);

  /* -- phase 2 - config file creation, if not exist -- */

  strcat(pad, "/");
  strcat(pad, progname);
  strcat(pad, ".conf");
  status = create_file(pad);

  isfileempty(pad);
  exit(0);

  
  if (status == -1) /* -- couldn't be created */
    return;

  /* -- phase 3 - if config file is empty, 
     populate with defaults -- */
  
  /* --- */
  if (isfileempty(pad)) {
    fp = fopen(pad, "w");

    if (fp == NULL) {
      perror(pad);
      return;
    }

    /* -- bench - home of projects  */
    fprintf(fp, "bench=%s\n", getenv("HOME"));
    fclose(fp);
  }
  
  /* -- phase 4 - load config -- */
  return;
}

void load_config(char *progname)
{
  return;
}

void dump_config(char *progname)
{
  return;
}

void remove_config(char *progname)
{
  return;
}
