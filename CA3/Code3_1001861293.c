// Inshaad Merchant 1001861293
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

void Merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[middle + 1 + j];
    }
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
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
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int L, int R)
{
    if (L < R)
    {
        int M = (L+R)/2;
        MergeSort(arr, L, M);
        MergeSort(arr, M+1, R);
        Merge(arr, L, M, R);
    }
}

void InsertionSort(int MyArray[] , int n)
{
    int i,j,key;
    for (j=1; j<n; j++)
    {
        key = MyArray[j];
        i = j-1;
        while (i>=0 && MyArray[i]>key)
        {
            MyArray[i+1] = MyArray[i];
            i = i-1;
        }
        MyArray[i+1] = key;
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
}

int main(int argc , char *argv[]) 
{ 
	clock_t start, end;
	//MERGE SORT
    int ArraySize = ReadFile(argc, argv);
    int *MyArray = CreateArray(argc,argv,ArraySize);
	
	//Print the unsorted array
    #ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
	    printf("\n\n\n");
	    
	#endif
	start = clock();
	MergeSort(MyArray, 0, ArraySize-1);
	end = clock();
	long Mtics = end - start;
	
	//Print the sorted array
	#ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
            printf("\n\n\n");
	    
	#endif
	
	free(MyArray); // freeing the array after merge sort.
	//END MERGE SORT
	
	//INSERTION SORT
	ArraySize = ReadFile(argc, argv);
	MyArray = CreateArray(argc,argv,ArraySize);
	//Print the unsorted array
    #ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
	    printf("\n\n\n");
	    
	#endif
	start = clock();
	InsertionSort(MyArray,ArraySize);
	end = clock();
	long Itics = end - start;
	//Print the sorted array
	#ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
	    printf("\n\n\n");
	    
	#endif
	
	free(MyArray); // freeing the array after insertion sort.
	//END INSERTION SORT

	printf("\n\nProcessed %d records\n",ArraySize);
	printf("Merge Sort: %ld tics\n", Mtics);
	printf("Insertion Sort: %ld tics\n", Itics);
	
	return 0; 
} 
