#include <stdio.h>
#include <ctype.h>
#include <string.h>
 
void printInt(int x)
{
  printf("%d\n", x);
}

int main(int argc, char **argv)
{
  if(argv[1] == NULL)
    printf("There are no arguments\n\n");
  else 
  {
    int maxIndex = 1;
    int max = strlen(argv[maxIndex]);

    for(int i=2;i<argc;i++)
      if(max < strlen(argv[i]))
      {        
        max = strlen(argv[i]);
        maxIndex = i;
      }
    printf("The biggest string is \'%s\'\n\n", argv[maxIndex]);
  }
}