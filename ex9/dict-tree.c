 #include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct node *tree_ptr;
struct node 
{
  Key_Type element; // only data is the key itself
  tree_ptr left, right;
  int collect_InsertInfo, collect_FindInfo, height;// add anything else that you need
};

struct table 
{
  tree_ptr head; // points to the head of the tree
  int total_Inserts, total_Finds;// add anything else that you need
};
struct node *new_Node(Key_Type data)
{
  struct node *node = (struct node*)malloc(sizeof(struct node));
  node->element = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}
Table initialize_table(/*ignore parameter*/) 
{
  struct table *newTable = (struct table *)malloc(sizeof(struct table));
  newTable->head = NULL;
  return newTable;
}

struct node *rightRotate(struct node *y)
{
  struct node *x = y->left;
  struct node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;
  x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

struct node *leftRotate(struct node *x)
{
  struct node *y = x->right;
  struct node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;
  y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

struct node *insertNode(struct node *tree, Key_Type key)
{
  if(tree == NULL) return new_Node(key);


  if(strcmp(key, tree->element) < 0)
  {tree->collect_InsertInfo++;tree->left = insertNode(tree->left, key);}

  else if(strcmp(key, tree->element) > 0)
  {tree->collect_InsertInfo++;tree->right = insertNode(tree->right, key);}

  return tree;
}
struct node *insertNodeAvl(struct node *tree, Key_Type key)
{
  // printf("%s\n", );
  if(tree == NULL)
    return new_Node(key);

  if(strcmp(key, tree->element) < 0)
    tree->left = insertNodeAvl(tree->left, key);
  else if(strcmp(key, tree->element) > 0)
    tree->right = insertNodeAvl(tree->right, key);
  else
    return tree;

  tree->height = 1 + getMax(getHeight(tree->left), getHeight(tree->right));

  int balance = getBalance(tree);

  if(balance > 1 && strcmp(key, tree->left->element) < 0)
    return rightRotate(tree);

  if(balance < -1 && strcmp(key, tree->right->element) > 0)
    return leftRotate(tree);

  if(balance > 1 && strcmp(key, tree->left->element) > 0)
  {
    tree->left = leftRotate(tree->left);
    return rightRotate(tree);
  }

  if(balance < -1 && strcmp(key, tree->right->element) < 0)
  {
    tree->right = rightRotate(tree->right);
    return leftRotate(tree);
  }
  return tree;
}
struct node *getModeInsert(struct node *tree, Key_Type k)
{
  switch (mode)
  {
    case 1:{
      return insertNode(tree, k);

    }break;
    case 2:{
      return insertNodeAvl(tree, k);

    }break;
  }
}
Table insert(Key_Type x,Table t) 
{
  t->total_Inserts++;
  Key_Type newKey = strdup(x);
  struct node *newNode = getModeInsert(t->head, newKey);
  t->head = newNode;
  return t;
}

struct node* search(struct node *tree, Key_Type key)
{
  if(tree == NULL)
    return tree;

  if(strcmp(tree->element, key) == 0)
  {
    tree->collect_FindInfo++;
    return tree;
  }
  if(strcmp(key, tree->element) > 0)
  {
    tree->collect_FindInfo++;
    return search(tree->right, key);
  }
  else
  {
    tree->collect_FindInfo++;
    return search(tree->left, key);
  }

}
Boolean find(Key_Type k, Table t) 
{
  t->total_Finds++;
  struct node *findElement = search(t->head, k);
  if(findElement != NULL)
    return TRUE;
  else
    return FALSE;
}
void retNode(struct node *tree)
{
  if(tree != NULL)
  {
    retNode(tree->left);
    printf("%s\n", tree->element);
    retNode(tree->right);
  }
}
int getInsertInfo(struct node *tree)
{
  if(tree == NULL)
    return 0;
  else
    return tree->collect_InsertInfo + getInsertInfo(tree->left) + getInsertInfo(tree->right);
}
int getHeight(struct node *tree)
{
  if(tree == NULL)
    return 0;
  else
  {
    int left = getHeight(tree->left);
    int right = getHeight(tree->right);

    if(left > right)
      return left + 1;
    else
      return right + 1;
  }
}
int getMax(int a, int b)
{
  return (a > b)? a : b;
}
int getFindInfo(struct node *tree)
{
  if(tree == NULL)
    return 0;
  else
    return tree->collect_FindInfo + getFindInfo(tree->left) + getFindInfo(tree->right);
}
int getBalance(struct node *tree)
{
  if(tree == NULL)
    return 0;
  return getHeight(tree->left) - getHeight(tree->right);
}
void print_table(Table t) 
{
  retNode(t->head);
}

void print_stats (Table t) 
{
  printf("Height of tree: %d\n", getHeight(t->head) - 1);
  printf("Average compares in insert method: %d\n", (getInsertInfo(t->head) / t->total_Finds) );
  printf("Average compares in find method: %d\n",(getFindInfo(t->head) / t->total_Finds));
}
