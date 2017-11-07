#include <stdio.h>
#include <ctype.h>

void initBoard(int length, int width, int board[][width])
{
  for(int i = 0; i < length; i++)
    for(int j = 0; j < length; j++)
      if((i + j) % 2 == 0)
        board[i][j] = 'O';
      else
        board[i][j] = ' ';
}
void printBoard(int length, int width, int board[][width])
{
  printf("Print board of size %d\n", length);
  for(int i =0; i <  length; i++)
  {
    for(int j = 0; j < width; j++)
      printf("%c", board[i][j]);
    printf("\n");
  }
}
int main(int argc, char **argv)
{
  int smallBoard[5][5];
  initBoard(5, 5, smallBoard);
  printBoard(5, 5, smallBoard);

  printf("\n");

  int bigBoard[20][20];
  initBoard(20, 20, bigBoard);
  printBoard(20, 20, bigBoard);
}