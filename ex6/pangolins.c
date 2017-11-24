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

  if(tree->type == QUESTION)
  {
    if(tree->yes != NULL)
    {
      if(tree->no != NULL)
        printf("Question: %s\nYes: %s\nNo: %s\n", tree->name, tree->yes->name, tree->no->name);
      else
        printf("Question: %s\nYes: %s\nNo: [NOTHING]\n", tree->name, tree->yes->name);
    }
    else
    {

      if(tree->no != NULL)
        printf("Question: %s\nYes: [NOTHING]\nNo: %s\n", tree->name, tree->no->name);
      else
        printf("Question: %s\nYes: [NOTHING]\nNo: [NOTHING]\n", tree->name);
    }
  }
  else
    printf("Object: %s\n", tree->name);

  printf("\n");
}

void treePrint(struct Tree *pangolins)
{
  if(pangolins == NULL)
    return;
  else
  {
    printNode(pangolins);
    treePrint(pangolins->no);
    treePrint(pangolins->yes);
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
  struct Tree *pizza = make("a pizza", OBJECT, NULL, NULL);
  struct Tree *monkey = make("a monkey", OBJECT, NULL, NULL);
  struct Tree *cat = make("a cat", OBJECT, NULL, NULL);
  struct Tree *isPizza = make("Is it flat, round and edible?", QUESTION,  pizza, cat);
  struct Tree *isMonkey = make("Does it have a tail?", QUESTION, monkey, isPizza);

  return isMonkey;
}


int main(int argc, char **argv) 
{
  struct Tree *pangolins = initTree();
  /*treePrint(pangolins);
  char *input;
  fgets(input,200,stdin);
  printf("%s\n", input);*/
  int isFin = 0;
  while(!isFin)
  {

    if(pangolins->yes == NULL && pangolins->no == NULL)
    {
      printf("Is it %s\n", pangolins->name);
      char *input = malloc(4 * sizeof(char));
      fgets(input,4,stdin);
      if(strcmp(input,"yes") == 0)
      {
        printf("I win!\n");
        isFin = 1;
      }
      else
      {
        printf("Oh. Well you win then\nWhat were you thinking of?\n");
        char *object = malloc(20 * sizeof(char));
        fgets(object, 1000, stdin);
        printf("Please give me a question about biscuit, so I can tell the difference between %s and %s\n", object, pangolins->name);
        char *question = malloc(100 * sizeof(char));
        fgets(question, 1000, stdin);
        printf("What is the answer to the question for %s\n", object);
        char *answer= malloc(4 * sizeof(char));
        fgets(answer, 1000, stdin);
        struct Tree *x = make(object, OBJECT, NULL, NULL);
        struct Tree *isX;
        if(strcmp(answer, "yes") == 0)
          isX = make(question, QUESTION, x, NULL);
        else
          isX = make(question, QUESTION, NULL, x);
        pangolins->no = isX;
        isFin = 1;
      }
    }
    else
    {
      printf("%s\n", pangolins->name);
      char *answer = malloc(4 * sizeof(char));
      fgets(answer,1000,stdin);
      if(strcmp(answer,"yes") == 0)
        pangolins=pangolins->yes;
      else
        pangolins=pangolins->no;
    }
  }
}
