#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char    *pippo()
{
  char  *retval = (char *)malloc(100);
  strcpy(retval, "pippo");
  free(retval);
  return (retval);
}

int     main()
{
  char  *var = pippo();
  sprintf("Stringa: %s\n", var);
  exit(0);
}
