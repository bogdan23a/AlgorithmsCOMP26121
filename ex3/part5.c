#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
void printInt(int x)
{
  printf("%d\n", x);
}

int main(int argc, char **argv)
{
  char *filename = argv[1];
  FILE *stream= fopen(filename, "r");
  int c;
  if (!stream)
  {
    if(filename == NULL)
      printf("You need to specify a file\n");
    else
    {
      char *name, *extension;
      name = strtok(filename, ".");;
      extension = strtok(NULL, ".");
      if(extension == NULL)
        printf("You need to specify the extension of the file\n\n");
      else
        if(strcmp(extension, "txt") == 0);
      else
        if(strcmp(name, "") == 0)
          printf("The name of the file can't be blanck\n\n");
      else printf("The extension must be .txt\n");

    }
  }
  else
  {
    
    int characters[255];
    for(int i=1;i<255;i++)
     characters[i]=0;
    while((c = fgetc(stream)) != EOF) 
    {
        characters[c]++;
    }

    for(int i=0;i<=255;i++)
      if(characters[i] != 0)
      printf("The number of \'%c\' characters is %d\n\n", i, characters[i]);
  }
}