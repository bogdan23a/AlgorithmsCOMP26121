#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tree
{
  tree *yes;
  tree *no;
  typedef enum question_or_object{QUESTION,OBJECT} type;
  char *name;
}*nodes;

void printNode()
{
  if(nodes->info.type == question_or_object.QUESTION)
    printf("Question: %s\nYes: %s\nNo: %s\n", nodes->name, nodes->yes->name,nodes->no->name);
  else
    printf("Object: %s\n", nodes->name);

}
int main(int argc, char **argv) 
{

}