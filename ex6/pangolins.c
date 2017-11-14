#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Tree
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

Tree *newTree(char *name, question_or_object type)
{
  Tree *returnValue = malloc(sizeof(Tree));  
  returnValue->name = name;
  returnValue->type = type;
  return returnValue;
}

void initTree()
{
  Tree pizza = makeObject("a pizza", question_or_object.OBJECT, NULL, NULL);
  Tree monkey = makeObject("a monkey", question_or_object.OBJECT, NULL, NULL);
  Tree cat = makeObject("a cat", question_or_object.OBJECT, NULL, NULL);
  Tree isPizza = makeObject("Is it flat, round and edible?", pizza, )
  Tree isMonkey = makeObject("Does it have a tail?", question_or_object.QUESTION, monkey, )

}

Tree makeObject(char *name, question_or_object type,char *yes, char *no,)
{
    *node = newTree(name,type);
    *node->yes = newTree(yes,)
    return node;


}
int main(int argc, char **argv) 
{

}