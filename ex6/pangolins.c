#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum question_or_object{QUESTION,OBJECT,NEITHER};
struct Tree
{
  struct Tree *yes;
  struct Tree *no;
  enum question_or_object type;
  char *name;
}*nodes;

void printNode(struct Tree *tree)
{

  if(tree->name != "")
  {
    if(tree->yes->name != "")
    {

      if(tree->no->name != "")
        printf("Question: %s\nYes: %s\nNo: %s\n", tree->name, tree->yes->name, tree->no->name);
      else
        printf("Question: %s\nYes: %s\nNo: [NOTHING]\n", tree->name, tree->yes->name);
    }
    else
    {

      if(tree->no->name != "")
        printf("Question: %s\nYes: [NOTHING]\nNo: %s\n", tree->name, tree->no->name);
      else
        printf("Question: %s\nYes: [NOTHING]\nNo: [NOTHING]\n", tree->name);
    }
  }
  
}

struct Tree *newTree(char *name, enum question_or_object type)
{
  struct Tree *returnValue = malloc(sizeof(struct Tree));  
  returnValue->name = name;
  returnValue->type = type;
  return returnValue;
}

struct Tree *make(char *name, enum question_or_object type,struct Tree *yes, struct Tree *no)
{
  struct Tree *node = newTree(name,type);
  node->yes = yes;

  node->no = no;
 
  return node;


}

struct Tree *initTree()
{
  struct Tree *neither = make("", NEITHER, NULL, NULL);
  struct Tree *pizza = make("a pizza", OBJECT, neither, neither);
  struct Tree *monkey = make("a monkey", OBJECT, neither, neither);
  struct Tree *cat = make("a cat", OBJECT, neither, neither);
  struct Tree *isPizza = make("Is it flat, round and edible?", QUESTION,  pizza, neither);
  struct Tree *isMonkey = make("Does it have a tail?", QUESTION, monkey, isPizza);

  return isMonkey;
}


int main(int argc, char **argv) 
{
  struct Tree *pangolins = initTree();
  printNode(pangolins);
  printNode(pangolins->yes);
  printNode(pangolins->no->no);
  printNode(pangolins->no);
}