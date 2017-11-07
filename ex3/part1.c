#include <stdio.h>
#include <ctype.h>

int largest(int array[], int length)
{
  int largest = array[0];

  for(int i = 1; i < length; i++)
    if(array[i] > largest)
      largest = array[i];
  return largest;
}
int main(int argc, char **argv)
{
  int x[9] = {10, 11, 12, 13, 14, 15, 16, 17, 18};
  int y[3] = {-1,2,-1};
  printf("Largest element in x = 10 11 12 13 14 15 16 17 18 is %d ", largest(x, 9));
  printf("\nLargest element in y = -1 2 -1 is %d\n", largest(y, 3));
  
}