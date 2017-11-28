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

void treePrint(struct Tree *pangolins,FILE *fp)
{
  
  if(pangolins == NULL)
    return;
  else
  {
    if(pangolins->type == QUESTION)
    {
      fprintf(fp, "Question:%s\n", pangolins->name);
      treePrint(pangolins->yes, fp);
      treePrint(pangolins->no, fp);
    }
    else
    {
      fprintf(fp, "Object:%s\n", pangolins->name);
    }
  }
  
}
void streePrint(struct Tree *pangolins)
{
  if(pangolins == NULL)
    return;
  else
  {
    if(pangolins->type == QUESTION)
    {
      printf("Question:%s\n", pangolins->name);
      streePrint(pangolins->yes);
      streePrint(pangolins->no);
    }
    else
    {
      printf("Object:%s\n", pangolins->name);
    }
  }
}

struct Tree *newTree(char *name, enum question_or_object type)
{
  struct Tree *returnValue = malloc(sizeof(struct Tree)); 
  // returnValue->name = malloc(strlen(name)*sizeof(char)); 
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
void freePan(struct Tree *p);
struct Tree *treeRead(FILE *fp,char *t, char *line)
{
  if(fgets(line,200 * sizeof(char),fp) == NULL)
    return newTree("[NEITHER]",NEITHER);
  else
  {
    t = strtok(line, ":");
      struct Tree *x = malloc(sizeof(struct Tree));
      x->name = malloc(100 * sizeof(char));

      if(strcmp(t,"Question") == 0)
      {
        t = strtok(NULL, ":\n");
        strcpy(x->name, t);
        x->type = QUESTION;
        x->yes = treeRead(fp,t,line);
        x->no = treeRead(fp,t,line);
      }
      else
      {
        t = strtok(NULL, ":\n");
        strcpy(x->name,t);
        x->type = OBJECT;
        x->yes = NULL;
        x->no = NULL;
       
      }
      return x;
  
  }
  
  // freePan(x);
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

struct Tree *insert(struct Tree *node, struct Tree *key, struct Tree *newE)
{
    if (node == key)
    {
      node = newE;
    }
    else if (node != key)
    { insert(node->no, key, newE);
      insert(node->yes, key, newE);}
}
void freePan(struct Tree *p)
{
  if(p != NULL)
  {
    freePan(p->yes);
    free(p->name);
    freePan(p->no);
    free(p);
  }
  else
  {

  }
}
int main(int argc, char **argv) 
{
  FILE *fp;
  fp = fopen("save.txt","r");
  char *line = malloc(200 * sizeof(char));
  char *t = malloc(100 * sizeof(char));
  struct Tree *pangolins = treeRead(fp,t,line);
  fclose(fp);
  free(line);
  free(t);
  struct Tree *start = pangolins;
  int isFin = 0;
  char *tokenized1 = malloc(100*sizeof(char));
  char *tokenized2 = malloc(100*sizeof(char));
  char *object = malloc(20 * sizeof(char));
  char *input = malloc(100 * sizeof(char));
  char *question = malloc(100 * sizeof(char));
  char *answer1 = malloc(100 * sizeof(char));
  char *answer2 = malloc(100 * sizeof(char));
  char *objectTokenized = malloc(20 * sizeof(char));
  char *answerTokenized = malloc(100 * sizeof(char));
  char *questionTokenized = malloc(100 * sizeof(char));

  while(!isFin)
  {

    if(pangolins->yes == NULL && pangolins->no == NULL)
    {
      printf("Is it %s\n", pangolins->name);
      
      fgets(input,100 * sizeof(char),stdin);

      
      char *tokenized1 = strtok(input, " \n");
      
      if(strcmp(tokenized1,"yes") == 0)
      {
        printf("I win!\n");
        free(object);
        free(question);
        isFin = 1;
        
      }
      else
      {
        printf("Oh. Well you win then\nWhat were you thinking of?\n");
        
        fgets(object, 20 * sizeof(char), stdin);
        char *objectTokenized = strtok(object,"\n");

        printf("Please give me a question about this, so I can tell the difference between %s and %s\n", objectTokenized, pangolins->name);
        
        fgets(question, 100 * sizeof(char), stdin);
        char *questionTokenized = strtok(question,"\n");

        printf("What is the answer to the question for %s\n", questionTokenized);

        fgets(answer1, 100 * sizeof(char), stdin);
        char *answerTokenized = strtok(answer1, "\n");

        struct Tree *saveNode = make(pangolins->name, pangolins->type, NULL,NULL);
        
        struct Tree *x = make(objectTokenized, OBJECT, NULL, NULL);
        
        struct Tree *isX = make(questionTokenized, QUESTION, NULL, NULL);
        
        if(strcmp(answerTokenized, "yes") == 0)
          {
            isX->yes = x;
            isX->no = saveNode;
          }
        else
          {
            isX->yes = saveNode;
            isX->no = x;
          }
        pangolins->name = isX->name;
        pangolins->type = isX->type;
        pangolins->yes = isX->yes;
        pangolins->no = isX->no;
        // free(saveNode->name);
        free(isX);
        // free(isX->name);
        // free(isX);
        // free(x->name);
        // free(x);
        FILE *fp = fopen("save.txt","w");
        treePrint(start, fp);
        fclose(fp);
        isFin = 1;
      }
    }
    else
    {
      printf("%s\n", pangolins->name);
      
      fgets(answer2,100 * sizeof(char),stdin);
      char *tokenized2 = strtok(answer2,"\n");

      if(strcmp(tokenized2,"yes") == 0)
        pangolins = pangolins->yes;
      else
        pangolins = pangolins->no;
    }
  }

  free(input);
  free(tokenized1);
  free(objectTokenized);
  free(questionTokenized);
  free(answer1);
  free(answerTokenized);
  free(answer2);
  free(tokenized2);
  freePan(start);
}
