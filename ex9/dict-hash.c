#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>
#include <math.h>
#include "speller.h"
#include "dict.h"

typedef enum {empty, in_use, deleted}state;

typedef struct 
{ // hash-table entry
  Key_Type element; // only data is the key itself
  state s;
} cell;

typedef unsigned long long Table_size; // type for size-of or index-into hash table

struct table 
{
  Table_size table_size; cell *cells; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  unsigned long long collisions;// add anything else that you need
};

Table initialize_table (Table_size size) 
{
  struct table *newTable = (struct table *)malloc(sizeof(struct table));
  newTable->cells = malloc(size * sizeof(cell));
  newTable->table_size = size;
  for(int i = 0; i< size;i++)
  {
    newTable->cells[i].element = NULL;
    newTable->cells[i].s = empty;
  }
  newTable->num_entries = 0;
  return newTable;
}
unsigned long long asciiHash(Key_Type key)
{
  unsigned long long sum = 0;
  for(unsigned long long i = 0; i < strlen(key); i++)
    sum += key[i];
   return sum;
}
unsigned long long polyHash(Key_Type key)
{
  unsigned long long a = 41;
  unsigned long long sum = 0;
  for(unsigned long long i = 0; i < strlen(key); i++)
    sum = a * sum + key[i];

  return sum;
}
unsigned long long linearProbing(Key_Type key, Table t)
{
  unsigned long long hashResult = (polyHash(key)) % t->table_size;
  int offset;
  for(offset = 1; offset <= t->table_size; offset++)
  {
    if(t->cells[hashResult].s == in_use)
    {
      if(!strcmp(t->cells[hashResult].element, key))
        return hashResult;
      t->collisions++;
      hashResult = (polyHash(key) + offset) % t->table_size;
    }
    else
      return hashResult;
  }
  return hashResult;
}
unsigned long long quadraticProbing(Key_Type key,Table t)
{
  unsigned long long hashResult = (polyHash(key)) % t->table_size;
  int offset;
  for(offset = 1; offset <= t->table_size; offset++)
  {
    if(t->cells[hashResult].s == in_use)
    {
      if(!strcmp(t->cells[hashResult].element,key))
        return hashResult;
      t->collisions++;
      hashResult = (polyHash(key) + offset * offset) % t->table_size;
    }
    else
      return hashResult;
  }
  return hashResult;
}
unsigned long long doubleHashing(Key_Type k, Table t)
{
  unsigned long long hashResult = (polyHash(k)) % t->table_size;
  int offset;
  for(offset = 1; offset < t->table_size; offset++)
  {
    if(t->cells[hashResult].s == in_use )
    {
      if(!strcmp(t->cells[hashResult].element,k) != 0)
        return hashResult;
      t->collisions++;
      hashResult = (polyHash(k) + offset * asciiHash(k)) % t->table_size;
    }
    else
      return hashResult;
  }
  return hashResult;
}
unsigned long long hash(Key_Type key, Table t)
{
  unsigned long long hashResult = 0;
  switch(mode)
  {
    //only linear probing with polynomial hashing
    case 1:
    {
      hashResult = linearProbing(key, t);

    }break;

    //quadraic probing with polynomial hashing
    case 2:
    {
      hashResult = quadraticProbing(key, t);
      
    }break;

    //doublehashing
    case 3:
    {
      hashResult = doubleHashing(key, t);

    }break;
  }
  return hashResult;
}
Table extendedSizeTable(Table t)
{
  if(t->table_size >= (t->num_entries + 1) / 2)
  {
    int newSize = t->table_size * 2;
    cell newCells[newSize];
    for(int i = 0; i <= t->table_size; i++)
    {
      newCells[i] = t->cells[i];
    }
    Table t = initialize_table(newSize + 1);
    for(int i = 0; i <= t->table_size; i++)
    {
      Key_Type newKey = strdup(newCells[i].element);
      unsigned long long newHash = hash(newKey, t);
      
      if(t->cells[newHash].element == NULL)
        t->num_entries++;

      t->cells[newHash].element = newKey;
      t->cells[newHash].s = in_use;
    }
  }
  return t;
}
Table insert (Key_Type k, Table t) 
{
  // t = extendedSizeTable(t);
  Key_Type newKey = strdup(k);
  unsigned long long newHash = hash(newKey,t);
  
  if(t->cells[newHash].element == NULL)
    t->num_entries++;

  t->cells[newHash].element = newKey;
  t->cells[newHash].s = in_use;

  return t;
}

Boolean find (Key_Type k, Table t) 
{
  if(t->cells[hash(k,t)].element == NULL)
    return FALSE;
  else 
    if(!strcmp(t->cells[hash(k,t)].element, k))
      return TRUE;
  return FALSE;
}

void print_table (Table t) 
{
  int i;
  for(i = 0; i < t->table_size; i++)
    if(t->cells[i].element != NULL)
      printf("%s\n", t->cells[i].element);
    else
      printf("<NULL>\n");
}

void print_stats (Table t) 
{
  printf("Number of collisions: %llu\n", t->collisions);
  printf("Size of table: %llu\n", t->table_size);
  printf("Number of entries: %llu\n", t->num_entries);

}
