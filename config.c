/* NAME
     config

   SYNOPSIS
     configure program parameters description: config is 
     to be called immediatelly after program starts. 

     It divided in 4 phases

     phase 1     
     If ~/.config dir not exists, create a new one

     phase 2
     If ~/.config/app dir not exists, create a new one

     phase 3
     if ~/.config/app/app.conf file, create a new one 
     to keep default parameters and insert initial ones

     phase 4	  
     If ~/.config/app.conf exists, load their
     parameters

  DEPENDENCIES
    stdio
    toolkit.lib

  BUGS
    - no switches or dialogs to select options
    - hardcoded parameters
    - if there is another app with same name using
      config dir, it will clash
    - buffer is limmited to 64 chars
    - parameters are isolated variables (not a struct)
      created: seg,  6 de jan de 2020 10:11:06
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <libgen.h>
#include "filetools.h"
#include "toolkit.h"
#include "config.h"

#define MAX_PAD 64
static char buffer[MAX_PAD];

const char * confdir = ".config_"; /* under HOME */

const int prjellen [] =
  {16, 32, 32, 16};

/* project elements */
enum prjels
{
 NAME,      /* name of project */
 GOAL,      /* goal of project */
 AUTHOR,    /* author of project */
 CREAT_DT   /* creation date of project */
};

const char *prjelnames [] =
{
 "name",
 "goal",
 "author",
 "creat_dt",
 NULL
};

typedef struct
{
  char name [17];
  char goal [33];
  char author [33];
  char creat_dt [17];
} project_t;

static project_t project;

static char *pn = project.name;
static char *pad = buffer;
static FILE *fp;
static long fsize;

static void load_defaults(void);
static void create_config_dir(void);
static void remove_config_dir(void);
static void create_config_file(void);
static void remove_config_file(void);
static int sumlen(int);
static int posel(char *);

int main(int argc, char *argv[])
{
  char *pn = project.name;
  if(argc < 2)
    strcpy(pn, basename(argv[0]));
  else
    strcpy(pn, argv[1]); 

  create_config();
  load_config();
  save_config();

  // dump_config();
  // remove_config();
  return 0;
}

void create_config(void)
{
  create_config_dir();
  create_config_file();
}

void load_config(void)
{
  /* -- phase 3 - if config file is empty,
        populate with defaults -- */
  sprintf(pad, "%s/%s/%s/%s.conf", getenv("HOME"), confdir, pn, pn);
  if (exist(pad)) { /* conf file exist, but is empty */
    if (getfsize(pad, &fsize)) {
      puts("config.conf exist and not empty"); /* TODO have to change this... just size not indicate file is empty */
      fp = fopen(pad, "r");
      if (fp == NULL) {
	perror(pad);
	return;
      }

      while(fgets(buffer, MAX_PAD, fp)) {
	if(!isprint(*buffer))
	  continue;
	//      puts(buffer);
	pad = strchr(buffer, ' ');
	*pad++ = 0;
	nputs(buffer);
	nputs(" = ");
	puts(pad);
	strcpy((char *) &project+sumlen(posel(buffer)), pad);
      }	  
      fclose(fp);
    }
    else { /* conf file exist, but is empty : populate it */
      getfsize(pad, &fsize);
      if (fsize == 0) {  
	load_defaults();
	save_config();
      }   
    }
  }
  return;
}

void save_config(void)
{
  /* fp = fopen(pad, "w"); */
  /* if (fp == NULL) { */
  /*   perror(pad); */
  /*   return; */
  /* } */

  /* /\* CHECKPOINT: the goal now is get default data, pre-initialized in structure project *\/ */

  /* while (*pn) { */
  /*   fprintf(fp, "%s %s\n", *pn, */
  /* 	   (char *) &project+sumlen(posel(*pn)) ); */
  /*   pn++; */
  /* } */
  /* fclose(fp); */
  return;
}

void dump_config(void)
{
  /* -- conf file */
  sprintf(pad, "%s/%s/%s/%s.conf", getenv("HOME"), confdir, pn, pn);
  fp = fopen(pad, "r");
  if (fp) {
    while (fgets(buffer, MAX_PAD, fp))
      nputs(buffer);
      
    fclose(fp);
  }
  return;
}

void remove_config(void)
{
  remove_config_file();
  remove_config_dir();
  return;
}

static int sumlen(int pos)
{
  /* return sum of lenghts of struct elements
     based on its position in the structure, calculating
     start pointer based on array of sizes of those
     elements 
  */
  int i, _sumlen=0;
  for (i = 0; i < pos; i++)
    _sumlen += prjellen [i];
  return _sumlen+i;
}

static int posel(char *elname) 
{
  /* return position of element on struct based on
     array of names of elments at struct */
  char **pn = (char **) prjelnames;
  int elctr = 0;
  
  while ( strcmp(elname, *pn++) )
    elctr++;

  return elctr;
}

static void load_defaults(void)
{
  time_t now = time(NULL);

  strncpy(project.goal, "goal of project",
	  prjellen[GOAL]);
  strncpy(project.author,  "author of project",
	  prjellen[AUTHOR]);
  strncpy(project.creat_dt, asctime(localtime(&now)),
	  prjellen[CREAT_DT]);
  puts(project.creat_dt);
}

static void remove_config_dir(void)
{
  /* -- conf dir remove */
  sprintf(pad, "%s/%s/%s", getenv("HOME"), confdir, pn);
  if (exist(pad)) 
    remove_dir(pad);
}

static void remove_config_file(void)
{
  /* -- conf file */
  sprintf(pad, "%s/%s/%s/%s.conf", getenv("HOME"), confdir, pn, pn);
  if (exist(pad)) 
    remove_file(pad);
}

static void create_config_dir(void)
{
  /* -- phase 1 - config dir/file creations */

  /* -- ~/.config - just in case it not exist */
  sprintf(pad, "%s/%s", getenv("HOME"), confdir);

  if (!exist(pad))
    create_dir(pad);

  /* - app dir creation - */
  /* warn: pad is a pointer to buffer previously initiated */
  /* I've used both, point to buffer and buffer to avoid 
     restrict warnings */
  sprintf(pad, "%s/%s", (char *) buffer, (char *)  pn);
  if (!exist(pad))
    create_dir(pad);
}

static void create_config_file(void)
{
  /* -- phase 2 - config file creation, if not exist -- */
  sprintf(pad, "%s/%s/%s/%s.conf", getenv("HOME"), confdir, pn, pn);

  if (!exist(pad))
    create_file(pad);
}
    /* char **peln= (char **) prjelnames; */
    /* puts ("pass"); */
    /* strcpy(project.name, "faa"); */
    /* strcpy(project.goal , "fee"); */
    /* strcpy(project.author , "fii"); */
    /* strcpy(project.creat_dt , "foo"); */
    /* while(*peln) { */
    /*   nputs("ueba: "); */
    /*   nputs(*peln); */
    /*   nputs("->"); */
    /*   puts(&project+sumlen(posel(*peln))); */
    /*   peln++; */
    /* } */
