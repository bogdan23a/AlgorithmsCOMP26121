#include <stdio.h>
#include <ctype.h>


void partA()
{
  char c = getchar();
  int totalChar = 0;
  int lowerToUpper = 0;
  int upperToLower = 0;
  while(c != '\n')
  {
    if(islower(c))
    { 
      putchar(toupper(c));
      lowerToUpper++;
    }
    else
    {
      putchar(tolower(c));
      upperToLower++;
    }
    c = getchar();
    totalChar++;
  }

  printf("\nRead %d characters in total, %d converted to upper-case, %d to lower-case", totalChar, lowerToUpper,upperToLower);

}

void partB()
{
  FILE *fp;
  fp = fopen("input.txt","rb");
  char a;
  int totalChar = 0;
  int lowerToUpper = 0;
  int upperToLower = 0;
  a = fgetc((FILE*) fp);
  putchar('\n');
  while(a != '\n')
  {

    if(islower(a))
    { 
      putchar(toupper(a));
      lowerToUpper++;
    }
    else
    {
      putchar(tolower(a));
      upperToLower++;
    }
    totalChar++;
    a = fgetc((FILE*) fp);
  }

  printf("\nRead %d characters in total, %d converted to upper-case, %d to lower-case", totalChar, lowerToUpper,upperToLower);

}

void partC()
{
  FILE *fp;
  FILE *wp;
  fp = fopen("input.txt","rb");
  wp = fopen("output.txt","w+");
  char a;
  int totalChar = 0;
  int lowerToUpper = 0;
  int upperToLower = 0;
  a = fgetc((FILE*) fp);
  fputc('\n',wp);
  while(a != '\n')
  {

    if(islower(a))
    { 
      fputc(toupper(a),wp);
      lowerToUpper++;
    }
    else
    {
      fputc(tolower(a),wp);
      upperToLower++;
    }
    totalChar++;
    a = fgetc((FILE*) fp);
  }
  fprintf(wp,"\nRead %d characters in total, %d converted to upper-case, %d to lower-case", totalChar, lowerToUpper,upperToLower);
  fclose(wp);

}
void partD()
{
  FILE *fp;
  FILE *wp;
  printf("name of file to read : ");
  char input[100] ;
  scanf("%s",input);
  printf("\nname of file to write : ");
  char output[100];
  scanf("%s", output);
  fp = fopen(input,"rb");
  wp = fopen(output,"w+");
  char a;
  int totalChar = 0;
  int lowerToUpper = 0;
  int upperToLower = 0;
  a = fgetc((FILE*) fp);
  fputc('\n',wp);
  while(a != '\n')
  {

    if(islower(a))
    { 
      fputc(toupper(a),wp);
      lowerToUpper++;
    }
    else
    {
      fputc(tolower(a),wp);
      upperToLower++;
    }
    totalChar++;
    a = fgetc((FILE*) fp);
  }
  fprintf(wp,"\nRead %d characters in total, %d converted to upper-case, %d to lower-case", totalChar, lowerToUpper,upperToLower);
  fclose(wp);
}
int main(int argc, char **argv)
{
  printf("PART A\n");
  partA();
  
  printf("\nPART B\n");
  partB();
  
  printf("\nPART C\n");
  partC();  
  
  printf("PART D\n");
  partD();
}
