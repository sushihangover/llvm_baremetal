#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

int main ()
{
  extern char _heap_start; /* Defined by the linker */
  extern char _heap_end; /* Defined by the linker */
  int i,n;
  char * buffer;

  i = 43;
  buffer = (char*) malloc (i);
  if (buffer==NULL)
  {
     puts ("Malloc failed\n");
     exit (1);
  }

  printf ("Printf string\n");
  for (n=0; n<i; n++) 
  {
    buffer[n]=rand()%26+'a';
  }
  buffer[i]='\0';
  printf ("Random string: %s\n",buffer);

  i = 32;
  do 
  {
     buffer = realloc(buffer, i);
     if (buffer == NULL) 
     {
        puts("Out of memory!\n");
        exit (1);
     } else {
        printf("%d bytes @ address 0x%X (Low=0x%X:Hi=0x%X)\n",
           i, 
           (unsigned int)buffer, 
           (unsigned int)&_heap_start,
           (unsigned int)&_heap_end
       );
       i = i + 32;
     }
  } while (buffer != NULL);
  
  exit(0); /* cause qemu to exit */
  return 0;
}

