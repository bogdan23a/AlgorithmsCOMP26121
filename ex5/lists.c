#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array 
*/

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
          "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};





/* declare your struct for a person here */
 struct Person{
  char *name;
  int age;
  struct Person *next;
};

int compare_people(struct Person *pers1, struct Person *pers2)
{
  return strcmp(pers1->name,pers2->name);
}

struct Person *newPerson()
{
  struct Person *returnValue = (struct Person*) malloc(sizeof(struct Person));

  if(returnValue == NULL)
    return NULL;

  returnValue->name = (char*) malloc(sizeof(char*));

  if(returnValue->name == NULL)
  {
   free(returnValue);
   return NULL;
  }

  return returnValue;
}


static struct Person *insertStart(struct Person *people, char *name, int age) 
{
  /* put name and age into the next free place in the array parameter here */
  struct Person* newP = newPerson();
  
  newP->name = name;
  newP->age = age;
  newP->next = people;
  /* modify nextfreeplace here */
  //(*nextfreeplace)++;
  //printf("%s %d\n", newP->name, newP->age);
  return newP;
}

static struct Person *insertEnd(struct Person *people, char *name, int age)
{
  struct Person* newP = newPerson();

  if(people == NULL)
  {
      newP->name = name;
    newP->age = age;
    newP->next = NULL;
    return newP;
  }
  else
  {
    struct Person *lastP = people;
    while(lastP->next != NULL)
      lastP = lastP->next;

    lastP->next = newP;
    newP->name = name;
    newP->age = age;
    newP->next = NULL;
    return people;
  }

}

static struct Person *insertSorted(struct Person *people, char *name, int age)
{
  struct Person* newP = newPerson();
  newP->name = name;
  newP->age = age;
  if(people == NULL || compare_people(people,newP) > 0)
  {
    newP->next = people;
    printf("%s\n",newP->name);
    return newP;
  }
  else
  {
    while(people->next != NULL && compare_people(people->next, newP) < 0)
      people = people->next;

    newP->next = people;
    people = newP;
    //printf("%s %d\n", newP->name, newP->age);

    return newP;
  }
}

int main(int argc, char **argv) 
{
  //int nextfreeplace = 0;

  /* declare the people array here */
  struct Person *people = NULL;
  for (int i = 0; i< HOW_MANY; i++) 
  {
    people = insertSorted(people, names[i], ages[i]);
  }

  //printf("\n");
  /* print the people array here*/
  while(people != NULL)
  {
    printf("%s %d\n", people->name, people->age);
    people = people->next;
  }


  while(people  != NULL)
  {
    free(people);
    free(people->name);
    people = people->next;
  }
  return 0;
}
