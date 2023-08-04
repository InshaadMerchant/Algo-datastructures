// Inshaad Merchant 1001861293
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

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
    int lines=0;
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
	       lines++;
	   }
	   fseek(fp, 0, SEEK_SET);
	   fclose(fp);
    }
    return lines;
}

int *CreateArray (int argc, char*argv[], int size)
{
    int *MyArray = (int *)malloc(size * sizeof(int));
    if (MyArray == NULL) 
    {
        printf("Memory allocation failed. Exiting......\n");
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
    printf("\n\n\n");
}

int main(int argc , char *argv[]) 
{ 
    clock_t start, end;
	
    int ArraySize = ReadFile(argc, argv);
    int *MyArray = CreateArray(argc,argv,ArraySize);
	
    #ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
	    
	#endif
	
	start = clock();
	InsertionSort(MyArray,ArraySize);
	end = clock();
	
	#ifdef PRINTARRAY
    
	    PrintArray(MyArray,ArraySize);
  	    printf("\n\nProcessed %d records\n",ArraySize);
 
	    
	#endif
  
        printf("Insertion Sort: %ld tics\n\n", end-start);
	
	free(MyArray); // freeing the array after insertion sort.
	
	return 0; 
} 

