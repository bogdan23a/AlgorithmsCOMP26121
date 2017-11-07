#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array 
*/
enum staff_or_student{
    STAFF,
    STUDENT,
    NEITHER
  };
union Data{
  char *programmeName;
  char *roomNumber;
};

#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
                        "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};
char *studentData[HOW_MANY] = {"", "", "", "COMP", "BMAN", "", ""};
char *staffData[HOW_MANY] = {"101", "201", "", "", "", "301", ""};
enum staff_or_student TYPE[HOW_MANY] = {STAFF, STAFF, NEITHER, STUDENT, STUDENT, STAFF, NEITHER};




/* declare your struct for a person here */
 struct Person{
  char *name;
  int age;
  struct Person *next;
  enum staff_or_student t;
  union Data *data;
};


int compare_people_by_name(struct Person *pers1, struct Person *pers2)
{
  return strcmp(pers1->name,pers2->name);
}

int compare_people_by_age(struct Person *pers1, struct Person *pers2)
{
  if(pers1->age > pers2->age)
    return 1;
  else
    if(pers1->age == pers2->age)
      return 0;
    else
    return -1;
}
struct Person *newPerson()
{

  struct Person *returnValue = (struct Person*) malloc(sizeof(struct Person));

  if(returnValue == NULL)
    return NULL;

  returnValue->data =(union Data*) malloc(sizeof(union Data));
  /*returnValue->name = (char*) malloc(sizeof(char));
  returnValue->t = (enum staff_or_student) malloc(sizeof(enum staff_or_student));
  
  returnValue->data->roomNumber =(char*) malloc(sizeof(char));
  returnValue->data->programmeName =(char*) malloc(sizeof(char));
  if(returnValue->name == NULL)
  {
   free(returnValue);
   return NULL;
  }
  if(returnValue->t == NULL)
  {
    free(returnValue);
    return NULL;
  }
  if(returnValue->data == NULL)
  {
    free(returnValue);
    return NULL;
  }
  if(returnValue->data->roomNumber == NULL)
  {
    free(returnValue);
    return NULL;
  }
  if(returnValue->data->programmeName == NULL)
  {
    free(returnValue);
    return NULL;
  }*/
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

static struct Person *insertSorted(struct Person *people, char *name, int age, 
                                   enum staff_or_student t, char *studentData, 
                                   char *staffData, int (*compare_people)())
{
  printf("s\n");
  struct Person* newP = newPerson();

  newP->name = name;

  newP->age = age;

  newP->t = t;

  newP->data->programmeName = studentData;
  
  newP->data->roomNumber = staffData;

  if(people == NULL || compare_people(people,newP) > 0)
  {
    newP->next = people;
    printf("%s %d %s %s %s\n", newP->name, newP->age, newP->t, 
                        newP->data->programmeName, newP->data->roomNumber);
    return newP;
  }
  else
  {
    struct Person *lastP = people;
    while(lastP->next != NULL && compare_people(lastP->next, newP) < 0)
      lastP = lastP->next;

    newP->next = lastP->next;
    lastP->next = newP;
    printf("%s %d %s %s %s\n", newP->name, newP->age, newP->t, 
                        newP->data->programmeName, newP->data->roomNumber);
    return people;
  }

}

int main(int argc, char **argv) 
{
  //int nextfreeplace = 0;

  /* declare the people array here */
  struct Person *people = NULL;
  for (int i = 0; i< HOW_MANY; i++) 
  {
    people = insertSorted(people, names[i], ages[i], TYPE[i], studentData[i], 
                          staffData[i] ,compare_people_by_age);
  }

  //printf("\n");
  /* print the people array here*/
  while(people != NULL)
  {
    printf("x\n");
    printf("%s %d %s %s %s\n", people->name, people->age, people->t, 
                        people->data->programmeName, people->data->roomNumber);
    people = people->next;

    
  }
  printf("%s %s\n", people->data->programmeName ,people->next->data->programmeName);

  while(people  != NULL)
  {
    /*free(people->data->programmeName);
    free(people->data->roomNumber);
    free(people->data);
    free(people->name);*/
    free(people);

    people = people->next;
  }
  return 0;
}
