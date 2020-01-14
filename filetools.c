#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>
#include "filetools.h"

static FILE *fp;
static struct stat statbuffer;
static int         status;

int create_dir(char *dirpath)
{
  return mkdir(dirpath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

int remove_dir(char *dirpath)
{
  return rmdir(dirpath);
}
int isdir(char *dirpath)
{
  status = stat(dirpath, &statbuffer);
  return (
	  (status == 0) &&  /* path exist */
	  S_ISDIR(statbuffer.st_mode)  /* is a dir */
	  );
}

int exist(char *path) /* just a wrapper */
{
  //  printf("checando se %s existe: %d, %d, d||d (%d)\n", path, isdir(path) , isfile(path), (isdir(path) || isfile(path)));
    
  return (isdir(path) || isfile(path));
}

int create_file(char *filename)
{
  status = EXIT_FAILURE;
  
  fp = fopen(filename, "w+");
  if (fp != NULL) {
    fclose(fp);
    status = EXIT_SUCCESS;
  }
  return status;
}

int remove_file(char *filename)
{
  return remove(filename);
}

int isfile(char *filepath)
{
  status = stat(filepath, &statbuffer);
  return (
	  (status == 0) &&  /* path exist */
	  S_ISREG(statbuffer.st_mode)  /* is a file */
	  );
}

int getfsize(char *filename, long *size)
{
  /* NAME */
  /*   getfsize - get file size */

  /* SYNOPSIS */
  /*   #include <stdio.h> */
  /*   #include "filetools.h" */
  /*   int getfsize(char* filename,long* size) */

  /* DESCRIPTION */
  /*   This function returns a disk file size. */
  /*   The getfsize() function shall return size in bytes */
  /*   of the file whose name is a string pointed by */
  /*   filename. */
  /*   The size argument will receive size returned by */
  /*   getfsize(). */
  /*   After a successful call to getfsize(), it will */
  /*   return EXIT_SUCCESS value. */
  /*   Otherwise, if the function getfsize() cannot find */
  /*   file or file cannot be accessed, it will return */
  /*   its diagnostics based on stdio.h common */
  /*   ERROR FLAGS. */

  /* CREATED */
  /* ter,  7 de jan de 2020 15:54:46 */
  
  status = EXIT_FAILURE;

  if (filename) {
    if (stat(filename, &statbuffer) != EXIT_SUCCESS)
      return status;
    *size = statbuffer.st_size;
    status = EXIT_SUCCESS;
  }
  return status;
}

