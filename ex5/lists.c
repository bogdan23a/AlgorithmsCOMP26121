#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



 struct Person{
  char *name;
  int age;
  struct Person *next;
  enum staff_or_student t;
  union Data data;
};
void printList(struct Person *people)
{

  while(people != NULL)
  {
      
    if(people->t == 0)
        printf("%s %d %s %s\n", people->name, people->age,"STAFF", 
                        people->data.roomNumber);
    else if(people->t == 1)
        printf("%s %d %s %s\n", people->name, people->age,"STUDENT", 
                        people->data.roomNumber);
    else
        printf("%s %d %s %s\n", people->name, people->age,"NEITHER", 
                        people->data.roomNumber);
    people = people->next;

  }
}

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
struct Person *newPerson(char *name, char *roomNumber, char *programmeName)
{
  struct Person *returnValue = (struct Person*) malloc(sizeof(struct Person));
  returnValue->name = (char*) malloc((strlen(name) - 1) * sizeof(char));
  returnValue->data.roomNumber =(char*) malloc((strlen(roomNumber) - 1) * sizeof(char));
  returnValue->data.programmeName =(char*) malloc((strlen(programmeName) - 1 ) * sizeof(char));
  
  if(returnValue == NULL)
    return NULL;
  return returnValue;
}


static struct Person *insertStart(struct Person *people, char *name, char *roomNumber, char *programmeName, int age) 
{
  struct Person* newP = newPerson(name,roomNumber,programmeName);
  newP->name = name;
  newP->age = age;
  newP->next = people;
  return newP;
}

static struct Person *insertEnd(struct Person *people, char *name, char *roomNumber, char *programmeName, int age)
{
  struct Person* newP = newPerson(name, roomNumber, programmeName);

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
//
//read data and creates lists elements accordingly
//
static struct Person *insertSorted(struct Person *people, char *name, int age, 
                                   enum staff_or_student t, char *studentData, 
                                   char *staffData, int (*compare_people)())
{
  struct Person* newP = newPerson(name, staffData, studentData);

  newP->name = name;

  newP->age = age;

  newP->t = t;

  if(studentData != "")
    newP->data.programmeName = studentData;
  else
     newP->data.roomNumber = staffData;

  if(people == NULL || compare_people(people,newP) > 0)
  {
    newP->next = people;
    return newP;
  }
  else
  {
    struct Person *lastP = people;
    while(lastP->next != NULL && compare_people(lastP->next, newP) < 0)
      lastP = lastP->next;

    newP->next = lastP->next;
    lastP->next = newP;
    return people;
  }

}
static struct Person *insert_sorted(struct Person *people, char *name, int age, 
                                   enum staff_or_student t, char *studentData, 
                                   char *staffData, int (*compare_people)())
{
  struct Person *newP = newPerson(name,staffData,studentData);
  
  newP->name = name;

  newP->age = age;

  newP->t = t;

  if(studentData != "")
    newP->data.programmeName = studentData;
  else
     newP->data.roomNumber = staffData;
  
  struct Person **ptr2ptr = NULL;
  struct Person *aux = people;
  ptr2ptr = &people;
  
  while((*ptr2ptr) != NULL && compare_people((*ptr2ptr), newP) < 0){
      *ptr2ptr = (*ptr2ptr)->next;
  }
  newP->next = *ptr2ptr;
  *ptr2ptr = newP;
  
  
 /* for(ptr2ptr = &people; *ptr2ptr != NULL; ptr2ptr = &(*ptr2ptr)->next)
  {
      printf("x\n");
      if(compare_people((*ptr2ptr),newP) < 0)
        *ptr2ptr = (*ptr2ptr)->next;
  }
  newP->next = *ptr2ptr;
  *ptr2ptr = newP;*/
  
 // printList(people);
  
  return people;
}
int main(int argc, char **argv) 
{
  struct Person *people = NULL;
  
  for (int i = 0; i< HOW_MANY; i++) 
  {
    people = insert_sorted(people, names[i], ages[i], TYPE[i], studentData[i], 
                          staffData[i] ,compare_people_by_age);
  }
  //
  //
  //
   
  printList(people);
   
  while(people  != NULL)
  {
    free(people->data.programmeName);
    free(people->data.roomNumber);
    free(people->name);
    free(people);

    people = people->next;
  }
  return 0;
}
