// Inshaad Merchant 1001861293
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>

typedef struct node
{
	int number;
	struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    NODE *TempPtr, *NewNode;
    NewNode = malloc(sizeof(struct node));
    NewNode->number = Number;
    NewNode->next_ptr = NULL;
    if (*LinkedListHead == NULL)
    {
    	*LinkedListHead = NewNode;
        return;
    }
    TempPtr = *LinkedListHead; // Start at the head
    
    /* Traverse the linked list to find the end node */
    while (TempPtr->next_ptr != NULL)
    {
        TempPtr = TempPtr->next_ptr;
        
    }
    
    /* Change end node to point to new node */
    TempPtr->next_ptr = NewNode;

}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
    int count =0, sum= 0;
    char data[50];
    if (argv[1] == NULL)
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }
    else
    {
       FILE *fp;
	   fp = fopen(argv[1] , "r");
	   while (fgets(data,sizeof(data),fp) != NULL)
	   {
	       int record = atoi(data);
	       AddNodeToLL(record,LLH);
	       sum += record;
	       count++;
	   }
	   printf("%d records were read for a total sum of %d\n", count, sum);
	   fclose(fp);
	   
    }
}

void PrintLL(NODE *LLH) 
{ 
    NODE *TempPtr;
    TempPtr = LLH;
    while (TempPtr != NULL)
    {
        printf("\n%p %d  %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        TempPtr = TempPtr->next_ptr;
    }
}

void FreeLL(NODE **LLH) 
{ 
    NODE *TempPtr, *next_ptr;
    TempPtr = *LLH;
    int record=0, sum=0, count=0;

    while (TempPtr != NULL) 
    {
        next_ptr = TempPtr->next_ptr;
        record = TempPtr->number;
        sum += record;
        #ifdef PRINT
	        printf("\n Freeing %p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        #endif
        free(TempPtr);
        TempPtr = next_ptr;
        count++;
    }
    printf("\n%d nodes were deleted for a total sum of %d\n", count, sum);
}

int main(int argc , char *argv[]) 
{ 
	NODE *LLH = NULL;
	clock_t start, end;
	
	/* capture the clock in a start time */
	start = clock();
    ReadFileIntoLL(argc, argv, &LLH);
	/* capture the clock in an end time */
	end = clock();
    printf("\n%ld tics to write the file into the linked list\n", end-start);
	
    #ifdef PRINT
    
	    /* capture the clock in a start time */
	    start = clock();
	    PrintLL(LLH);
	    /* capture the clock in an end time */
	    end = clock();
	    printf("\n%ld tics to print the linked list\n", end-start);
	    
	#endif
	
    /* capture the clock in a start time */
	start = clock();
	FreeLL(&LLH);
	/* capture the clock in an end time */
	end = clock();
	printf("\n%ld tics to free the linked list\n", end-start);
	
	return 0; 
} 

