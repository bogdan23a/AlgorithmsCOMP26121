#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long dl(unsigned long long result, unsigned long long base, unsigned long long mod)
{
  unsigned long long currentPower;
  for(int i = 1; i < mod; i++)
  {
    currentPower = 1;
    for(int j = 1; j <= i; j++)
      currentPower *= base;
    if(currentPower % mod == result)
      return i;
  }
}

int main(int argc, char **argv) 
{

  char *input1 = malloc(100 * sizeof(char));
  char *base = malloc(100 * sizeof(char));
  char *input2 = malloc(100 * sizeof(char));
  char *prime = malloc(100 * sizeof(char));
  char *input3 = malloc(100 * sizeof(char));
  char *result = malloc(100 * sizeof(char));

  printf("Enter your base: ");

  fgets(input1, 100 * sizeof(char), stdin);
  base = strtok(input1, ": \n");


  printf("Enter your prime number: ");

  fgets(input2, 100 * sizeof(char), stdin);
  prime = strtok(input2, ": \n");

  printf("Enter your result: ");

  fgets(input3, 100 * sizeof(char), stdin);
  result = strtok(input3, ": \n");

  printf("%d,%d,%d\n", atoi(base),atoi(prime),atoi(result));
  printf("Your exponent is: %d\n", dl(atoi(result), atoi(base), atoi(prime)));
}