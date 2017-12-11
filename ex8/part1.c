#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;

B *list;

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

int comp_on_rating(struct book *a, struct book *b)
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

int comp_on_relev(struct book *a, struct book *b)
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

int comp_on_price(struct book *a, struct book *b)
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

// void swap(int *a, int *b)
// {
//   int t=*a;
//   *a = *b;
//   *b = t;
// }
// int partition(int arr[], int low, int high)
// {
//   int pivot = arr[high];
//   int i = (low - 1);

//   for(int j = low; j <= high - 1; j++)
//   {
//     if(arr[j] <= pivot)
//     {
//       i++;

//       swap(&arr[i], &arr[high]);
//       return (i + 1);
//     }
//   }
// }
// void quickSort1(int arr[], int N)
// {
//   int low = 1;
//   int high = N;
//   if(low < high)
//   {
//     int pi = partition(arr, low, high);
//     quickSort(arr, low, pi - 1);
//     quickSort(arr, pi + 1, high);
//   }
// }
/*void quickSort(struct book arr[], int low, int high, int (*compar)(const void *, const void *))
{

  if(low < high)
  {
    int i = low, j = high;
    const void *x;
    ((struct book*)x) = arr[(i + j) / 2];
    const void *current;
    *((struct book*)current) = arr[i];
    do{
      while(compar(current,x) < 0) i++;
      while(compar(x,current) < 0) j--;

      if(i <= j)
      {
        struct book temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
      }

    } while(i <= j);

    quickSort(arr, low, j, compar);
    quickSort(arr, i, high, compar);
  }
}*/


void merge(struct book arr[], int l, int m, int r, int (*compar)(struct book *, struct book *))
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  struct book L[n1], R[n2];

  for(i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for(j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;

  while(i < n1 && j < n2)
  {
    if(compar(&L[i], &R[j]))
    {
    // printf("(Hai ca se poate cu %d si %d)\n", l, r);
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while(i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  while(j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }


}

void mergeSort(struct book arr[], int l, int r, int (*compar)(struct book *, struct book *))
{

  if(l < r)
  {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m, compar);
    mergeSort(arr, m + 1, r, compar);

    merge(arr, l, m, r, compar);
  }
}
void user_interface(int N)
{

  // For Part 1 this function calls the sort function to sort on Price only
  mergeSort(list, 1,  N, comp_on_relev);
  

  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function
  

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
  
  N=read_file(argv[2], N);
  
  user_interface(N);
  
  print_results(N);

  return(0);
}

