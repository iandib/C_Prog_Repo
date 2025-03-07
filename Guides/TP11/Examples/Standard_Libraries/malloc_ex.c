/* malloc example: random string generator*/
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

int main (void)
{
  int len, n;
  char * buffer;

  printf ("How long do you want the string? ");
  scanf ("%d", &len);

  buffer = (char*) malloc (len+1);
  if (buffer!=NULL)
  {
    for (n=0; n<len; n++)
      buffer[n]=rand()%('z'-'a'+1)+'a';
    buffer[len]='\0';
   
    printf ("Random string: %s\n",buffer);
    free (buffer);
  }
  return 0;
}
