#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;

B *list, *save;

int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);	  
	  c++;
	}
      fclose(fp);      
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {  
     return -1;
  }
    else 
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }  
}

int comp_on_relev(const void *a, const void *b)
{
 
  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {  
     return -1;
  }
     else 
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     { 
       return 1;
     }
       else
     {
       return 0;
     }
  }  
}

int comp_on_price(const void *a, const void *b)
{
 
  if ((*(B *)a).price < (*(B *)b).price)
  { 
     return 1;
  }
     else 
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }  
}

void merge(int l, int m, int r, int (*compar)(const void *, const void *))
{
  int i, j, k;

  int n1 = m - l + 1;
  int n2 =  r - m;

  B *L, *R;
  L = (B *)malloc(n1*sizeof(B));
  R = (B *)malloc(n2*sizeof(B));



  for(i = 0; i < n1; i++)
    L[i] =  list[l + i];
  for(j = 0; j < n2; j++)
    R[j] = list[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while(i < n1 && j < n2)
  {
    if((compar)(&L[i], &R[j]) >= 0)
    {
      list[k] = L[i];
      i++;
    }
    else
    {
      list[k] = R[j];
      j++;
    }
    k++;
  }

  while(i < n1)
  {
    list[k] = L[i];
    i++;
    k++;
  }

  while(j < n2)
  {
    list[k] = R[j];
    j++;
    k++;
  }

}

void mergeSort(int l, int r, int (*compar)(const void *, const void *))
{
  int m;
  if(l < r)
  {
    m = l + (r - l) / 2;
    // printf("(Hai ca nu se poate cu %d si %d)\n", l, r);
    mergeSort(l, m, compar);
    mergeSort(m + 1, r, compar);

    merge(l, m, r, compar);
  }
}
void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only
  // mergeSort(0,  N-1, comp_on_relev);
  char *first = malloc(100 * sizeof(char));
  char *firstTok = malloc(100 * sizeof(char));
  char *second = malloc(100 * sizeof(char));
  char *secondTok = malloc(100 * sizeof(char));
  char *third = malloc(100 * sizeof(char));
  char *thirdTok = malloc(100 * sizeof(char));
  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function
  printf("Would you like to do lexicographic sort?\n");
  fgets(first, 100 * sizeof(char), stdin);
  firstTok = strtok(first, " \n");

  if(strcmp(firstTok, "yes") == 0)
  {
    printf("How many fields do you want to specify( up to 3)?\n");
    fgets(second, 100 * sizeof(char), stdin);
    secondTok = strtok(second, "\n");

    int keysNumber = atoi(secondTok);
    int keys[keysNumber];

    int i;
    printf("Choose your sorting key: rating(0), relevance(1), price(2)\n");

    for(i = 0; i < keysNumber; i++)
    {
      printf("Enter your key for relevance %d: ", i);
      fgets(third, 100 * sizeof(char), stdin);
      thirdTok = strtok(third, " \n");

      int sortToKey = atoi(thirdTok);
      keys[i] = sortToKey;
    }

    printf("Your input:\n");
    for(i = 0; i < keysNumber; i++)
      printf("Key with importance %d is %d\n", i, keys[i]);
    printf("\n");

    for(i = 0; i < keysNumber; i++)
    {
      if(keys[i] == 0)
        qsort(list, N, sizeof *list, comp_on_rating);
      else if( keys[i] == 1 )
        qsort(list, N, sizeof *list, comp_on_relev);
      else
        qsort(list, N, sizeof *list, comp_on_price);
    }
  }
  else
    mergeSort(0, N - 1, comp_on_price);

}
 

void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {  
    printf("%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
    fprintf(fp, "%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
    
      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}


int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));

  save = (B *)malloc(N*sizeof(B));
  
  N=read_file(argv[2], N);
  
  user_interface(N);
  
  print_results(N);

  return(0);
}

