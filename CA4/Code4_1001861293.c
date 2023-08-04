// Inshaad Merchant 1001861293
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void swap(int *SwapA, int *SwapB)
{
    int temp = *SwapA;
    *SwapA = *SwapB;
    *SwapB = temp;
}

int partition (int A[], int low, int high)
{
    int i, j = 0;

    #if QSM
    int middle = (high+low)/2;
    swap(&A[middle] , &A[high]);
    #elif QSRND
    int random = (rand() % (high-low+1)) + low;
    swap(&A[random] , &A[high]);
    #endif

    int pivot = A[high];
    i = (low - 1);
    for (j = low; j < high; j++)
    {
        if (A[j] < pivot)
        {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return (i + 1);
}

void QuickSort(int MyArray[], int low, int high)
{
    if (low < high)
    {
        int ndx = partition(MyArray, low, high);
        QuickSort(MyArray, low, ndx - 1);
        QuickSort(MyArray, ndx + 1, high);
    }
}

int ReadFile(int argc,  char *argv[])
{
    char FileLine[50];
    int count=0;
    if (argv[1] == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }
    else
    {
       FILE *fp;
	   fp = fopen(argv[1] , "r");
	   while (fgets(FileLine,sizeof(FileLine),fp) != NULL)
	   {
	       count++;
	   }
	   fseek(fp, 0, SEEK_SET);
	   fclose(fp);
    }
    return count;
}

int *CreateArray (int argc, char*argv[], int size)
{
    int *MyArray = (int *)malloc(size * sizeof(int));
    if (MyArray == NULL) 
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    
    int i = 0;
    FILE *fp;
	fp = fopen(argv[1] , "r");
    char FileLine[100]; // Assuming maximum line length of 100 characters
    while (fgets(FileLine, sizeof(FileLine), fp) != NULL) 
    {
        MyArray[i] = atoi(FileLine); // Convert the line to an integer and store in array
        i++;
    }
    fclose(fp);
    return MyArray;
}

void PrintArray(int MyArray[], int n)
{
    
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d\n", MyArray[i]);
    }    
    printf("\n\n");
}

int main(int argc , char *argv[]) 
{ 
    clock_t start, end;
    int numberofruns = 0;
    int total=0, avg=0;
    //QUICK SORT
    if (argv[2] == NULL)
    {
      printf("Number of runs not specified on command line...defaulting to 10\n");
      numberofruns = 10;
    }
    else
    {
      numberofruns = atoi(argv[2]);
    }
    int ArraySize = ReadFile(argc, argv);
    for(int i=0; i< numberofruns; i++)
    {
        int *MyArray = CreateArray(argc,argv,ArraySize);
    	//Print the unsorted array
    	#ifdef PRINTARRAY
	     PrintArray(MyArray,ArraySize);
    	#endif
	
    	start = clock();
    	QuickSort(MyArray, 0, ArraySize-1);
    	end = clock();
	total += (end - start);
    	//Print the sorted array
    	#ifdef PRINTARRAY
	    PrintArray(MyArray,ArraySize);
    	#endif
	printf("Run %d complete: %ld tics\n", (i+1), end-start);
        free(MyArray); // freeing the array after quick sort
    }
    avg = total / numberofruns;
    printf("The average run time for %d runs is %d\n\n", numberofruns, avg);
    //END QUICK SORT
    printf("\n\nProcessed %d records\n", ArraySize);

    return 0; 
} 



