#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
float c2f(float c)
{
  return 9*c/5 + 32;
}
float f2c(float f)
{
  return (f - 32) / (9/5);
}
void printFloat(double x)
{
  printf("%.2f\n", x);
}
int main(int argc, char **argv)
{
  if(argv[1] == NULL)
    printf("There are no arguments\n\n");
  else
    if(strcmp(argv[1],"-c") != 0 && strcmp(argv[1],"-f") != 0)
      printf("Flag not available. Use -f or -c for farenheight or celsius specification \n\n");
  else if(argv[2] == NULL)
    printf("You need to give a number\n\n");
  else if(argv[3] != NULL)
    printf("Third argument not available\n");
  else 
  {
    double s = atof(argv[2]);
    if(strcmp(argv[1],"-f") == 0)
    {  
      if(s < 0)
        printf("Number below absolute 0\n\n");
      else
        printf("%.2f °C = %.2f °F\n\n", s, f2c(s));
    }
    else if(strcmp(argv[1],"-c") == 0)
    {  
      if(s < -273.15)
        printf("Number below absolute 0\n\n");
      else
        printf("%.2f °C = %.2f °F\n\n", c2f(s), s);
    }
   
  }
}