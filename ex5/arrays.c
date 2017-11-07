#include <stdio.h>
#include <stdlib.h>
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
};


struct Person *newPerson()
{
  struct Person *returnValue = (struct Person*) malloc(sizeof(struct Person));

  if(returnValue == NULL)
    return NULL;

  returnValue->name = (char*) malloc(sizeof(char[30]));

  if(returnValue->name == NULL)
  {
   free(returnValue);
   return NULL;
  }

  return returnValue;
}


static void insert(struct Person *people[], char *name, int age, int *nextfreeplace) 
{
  /* put name and age into the next free place in the array parameter here */
  people[*nextfreeplace] = newPerson();
  people[*nextfreeplace]->name = name;
  people[*nextfreeplace]->age = age;
  /* modify nextfreeplace here */
  (*nextfreeplace)++;
}

int main(int argc, char **argv) 
{
  int nextfreeplace = 0;

  /* declare the people array here */
  struct Person *people[HOW_MANY] ;
  for (int i = 0; i< HOW_MANY; i++) 
  {
    insert (people, names[i], ages[i], &nextfreeplace);
  }

  /* print the people array here*/
  for( int i = 0; i < HOW_MANY; i++)
    printf("%s %d\n", people[i]->name,people[i]->age);

  for(int i = 0; i < HOW_MANY; i++)
    free(people[i]);
  return 0;
}
