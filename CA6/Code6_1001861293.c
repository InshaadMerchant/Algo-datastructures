// Coding Assignment 6 - Inshaad Merchant - 1001861293

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 30
 
/* Node for storing information */
typedef struct LegendaryCricketers
{
    char *name;
    float battingAverage;
    char *country;
    int age;
    struct LegendaryCricketers *next_ptr;
}
LEGENDARYCRICKETERS;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(LEGENDARYCRICKETERS *NewNode, LEGENDARYCRICKETERS *Alltimebest[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (Alltimebest[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		Alltimebest[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		LEGENDARYCRICKETERS *TempPtr = Alltimebest[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(LEGENDARYCRICKETERS *Alltimebest[])
{
	LEGENDARYCRICKETERS *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Alltimebest[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				//free(TempPtr->battingAverage);
				//free(TempPtr->country);
				//free(TempPtr->age);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteCricketer(LEGENDARYCRICKETERS *Alltimebest[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Cricketer to delete from the Alltimebest ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	LEGENDARYCRICKETERS *TempPtr = Alltimebest[HashIndex];
	LEGENDARYCRICKETERS *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nCricketer %s does not exist in the Alltimebest\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Alltimebest[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Alltimebest[HashIndex] = TempPtr->next_ptr;
					printf("\nCricketer %s has been deleted from the Alltimebest\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nCricketer %s has been deleted from the Alltimebest\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nCricketer %s does not exist in the Alltimebest\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(LEGENDARYCRICKETERS *Alltimebest[])
{
	int i;
	LEGENDARYCRICKETERS *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Alltimebest[i];

		printf("\nAlltimebest[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(LEGENDARYCRICKETERS *Alltimebest[])
{
	int i;
	LEGENDARYCRICKETERS *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Alltimebest[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(LEGENDARYCRICKETERS *Alltimebest[])
{
	LEGENDARYCRICKETERS *TempPtr = NULL;
	char battingAverage[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Cricketer's name ");
	fgets(LookupName,sizeof(LookupName),stdin);
	
        if(LookupName[0] == '\n')
        {
		fgets(LookupName,sizeof(LookupName),stdin);
        }
        if(LookupName[strlen(LookupName)-1] == '\n')
	{
		LookupName[strlen(LookupName)-1] = '\0';
	}
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Alltimebest[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
					printf("\n");
					printf("Batting Average\t\t%.2f\n", TempPtr->battingAverage);
					printf("Country\t\t\t%s\n", TempPtr->country);
					printf("Age\t\t\t%d\n", TempPtr->age);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nCricketer %s not found in Alltimebest\n\n", LookupName);
}

void AddNewCricketer(LEGENDARYCRICKETERS *Alltimebest[])
{
	int HashIndex = 0;
	LEGENDARYCRICKETERS *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(LEGENDARYCRICKETERS));
	NewNode->next_ptr = NULL;

	printf("\n\nEnter new Cricketer's name ");
	scanf("%s", TempBuffer);
	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's batting average", NewNode->name);
	scanf("%f", &(NewNode->battingAverage));
	
	printf("\n\nEnter %s's country of origin ", NewNode->name);
	scanf("%s", NewNode->country);
	
	printf("\n\nEnter %s's possible age ", NewNode->name);
	scanf(" %d", &(NewNode->age));

	// Extra fgets to clear stdin
	fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);

	AddNode(NewNode, Alltimebest);
}

int ReadFileIntoHashTable(int argc, char *argv[], LEGENDARYCRICKETERS *Alltimebest[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	LEGENDARYCRICKETERS *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH) != NULL)
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(LEGENDARYCRICKETERS));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->battingAverage = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->country = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->country, token);

			token = strtok(NULL, "|");
			NewNode->age = atoi(token);

			AddNode(NewNode, Alltimebest);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	LEGENDARYCRICKETERS *Alltimebest[HASHTABLESIZE] = {};

	//enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Alltimebest);
 
	do
	{
		printf("\n\nCricketers Menu\n\n"
			   "1. Show all Cricketers in Alltimebest for a given letter\n"
			   "2. Look up Cricketer by name\n"
			   "3. How many Cricketers are in the Alltimebest?\n"
			   "4. Display the Alltimebest\n"
			   "5. Add a new Cricketer\n"
			   "6. Delete a Cricketer from the Alltimebest\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case 1:
				ShowByLetter(Alltimebest);
				break;
			case 2:
				ShowByName(Alltimebest);
				break;
			case 3:
				printf("Your Alltimebest contains %d Cricketers\n", counter); 
				break;
 			case 4:
				DisplayHashTable(Alltimebest);
				break;
			case 5:
				AddNewCricketer(Alltimebest);
				counter++;
				break;
			case 6:
				if (DeleteCricketer(Alltimebest))
				{
					counter--;
				}
				break;
			case 7:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != 7);
	
	FreeDynamicMemory(Alltimebest);

	return 0;
}			  
