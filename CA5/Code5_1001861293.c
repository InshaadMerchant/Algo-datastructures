//Inshaad Merchant 1001861293
#include <stdio.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <time.h>
#include <limits.h>

#define MAX_SIZE 50

typedef struct 
{
    char label[100];
    int distance;
    int previous;
    int visited;
} Vertex;

void Dijkstra(int StartVertex, int VertexCount, int Adjacencymatrix[MAX_SIZE][MAX_SIZE], Vertex Label[MAX_SIZE], int endVertex) 
{
    Vertex VertexArray[MAX_SIZE] = {};
    int path[MAX_SIZE] = {};
    int currentVertex = StartVertex;
    VertexArray[StartVertex].distance = 0;
    VertexArray[StartVertex].previous = -1;
    VertexArray[StartVertex].visited = 1;
    int SmallestVertexIndex = -1;

    for (int i = 0; i < MAX_SIZE; i++) 
    {
        VertexArray[i].distance = INT_MAX;
    }
    VertexArray[StartVertex].distance = 0;

    for (int x = 0; x < VertexCount - 1; x++) 
    {
        for (int i = 0; i < VertexCount; i++) 
        {
            if (Adjacencymatrix[currentVertex][i] != -1 && !VertexArray[i].visited) 
            {
                if (VertexArray[currentVertex].distance + Adjacencymatrix[currentVertex][i] < VertexArray[i].distance) 
                {
                    VertexArray[i].distance = VertexArray[currentVertex].distance + Adjacencymatrix[currentVertex][i];
                    VertexArray[i].previous = currentVertex;
                }
            }
        }

        SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        for (int i = 0; i < VertexCount; i++) 
        {
            if (!VertexArray[i].visited && VertexArray[i].distance < SmallestVertex)
            {
                SmallestVertex = VertexArray[i].distance;
                SmallestVertexIndex = i;
            }
        }

        currentVertex = SmallestVertexIndex;
        VertexArray[currentVertex].visited = 1;
    }

    #ifdef PRINTIT
    printf("\t\t\t\t Vertex Array\n");
    printf("I\t\tL\t\tD\t\tP\t\tV\n");
    for (int i = 0; i < VertexCount; i++) 
    {
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\n", i, Label[i].label, VertexArray[i].distance, VertexArray[i].previous, VertexArray[i].visited);
    }
    #endif

    path[0] = endVertex;
    printf("From %s to %s:\n Distance is %d\n Path is ", Label[StartVertex].label, Label[endVertex].label, VertexArray[endVertex].distance);
    int d = 1;
    int f = 1;
    currentVertex = path[0];
    while (currentVertex != StartVertex) 
    {
        path[d] = VertexArray[currentVertex].previous;
        currentVertex = path[d];
        d++;
        f++;
    }

    while (f > 0) 
    {
        f--;
        if (path[f] != -1) 
        {
            printf("%s", Label[path[f]].label);
            if (f > 0) 
            {
                printf("->");
            }
        }
    }
    printf("\n");
}

int ReadFile(int Adjacencymatrix[MAX_SIZE][MAX_SIZE],  char *argv[], int *topasscount, char startingVertex[6], Vertex Label[6], char destination[6], int *topassendcount)
{
    char FileLine[100];
    FILE *fp;
    fp = fopen(argv[1],"r");
    int k = 0, VertexCount = 0;
    int count = -1;
    char *Token, *token_2;
    if (fp == NULL)
    {
        printf("File can't be opened......Exiting\n");
        exit(0);
    }
    while(!feof(fp))
    {
        fgets(FileLine, 100, fp);
        VertexCount++;
    }
    fseek(fp, 0, SEEK_SET);
    printf("Enter your starting vertex: ");
    scanf("%s", startingVertex);
    printf("Enter your end vertex: ");
    scanf("%s", destination);
    while(!feof(fp))
    {
        fgets(FileLine, 100, fp);
        count++;
        if(FileLine[strlen(FileLine) - 1] == '\n')
        {
            FileLine[strlen(FileLine) - 1] = '\0';
        }
        Token = strtok(FileLine, ",");
        char vertexLabel[100];
        strcpy(vertexLabel, Token);
        strcpy(Label[k].label, vertexLabel);
        k++;
        if(strcmp(Token, startingVertex) == 0)
        {
           (*topasscount) = count;
        }
        if(strcmp(Token, destination) == 0)
        {
           (*topassendcount) = count;
        }
        int p = 0;
        while(p != 1)
        {
            Token = strtok(NULL, ",");
            if (Token == NULL)
            {
                p = 1;
            }
            token_2 = strtok(NULL, ",");
            if (token_2 == NULL)
            {
                p = 1;
            }
            if(Token != NULL && token_2 != NULL)
            {
                Adjacencymatrix[count][atoi(Token)] = atoi(token_2);
            }
            Token = strtok(NULL, ",");
            if (Token == NULL)
            {
                p = 1;
            }
            token_2 = strtok(NULL, ",");
            if (token_2 == NULL)
            {
                p = 1;
            }
            char weight_2[1];
            if(Token != NULL && token_2 != NULL)
            {
                Adjacencymatrix[count][atoi(Token)] = atoi(token_2);
            }
        }
    }
    fclose(fp);
    return VertexCount;
}
void PrintArray(int Adjacencymatrix[MAX_SIZE][MAX_SIZE], int VertexCount)
{
    for (int i = 0; i < VertexCount; i++) 
    {
        for (int j = 0; j < VertexCount; j++) 
        {
            printf("%d\t\t", Adjacencymatrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[])
{
    int Adjacencymatrix[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) 
    {
        for (int j = 0; j < MAX_SIZE; j++) 
        {
            Adjacencymatrix[i][j] = -1;
        }
        printf("\n");
    }
    int topasscount, topassendcount;
    char startVertexChar[6] = {}, endVertex[6] = {};
    Vertex VertexLabel[6];
    int VertexCount = ReadFile(Adjacencymatrix, argv, &topasscount, startVertexChar, VertexLabel, endVertex, &topassendcount);

    #ifdef PRINTIT
    printf("\t\t\t\t\tAdjacency Matrix\n");
    PrintArray(Adjacencymatrix, VertexCount);
    printf("\n");
    #endif

    Dijkstra(topasscount, VertexCount, Adjacencymatrix, VertexLabel, topassendcount);

    return 0;
}
