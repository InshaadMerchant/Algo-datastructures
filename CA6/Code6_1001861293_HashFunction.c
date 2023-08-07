#include <stdio.h>
#define HASHTABLESIZE 10
int MyHashFunction(char value[])
{
    //perform hash method
    int value = 0, count = 0;
    while(count < strlen(value))
    {
        value = value + value[count];
        count++;
    }
    printf("the value is %d", value);
    return value % HASHTABLESIZE;
}
int main(void)
{
    char HashValue[20];
    printf("Enter value ");
    fgets(HashValue,sizeof(HashValue),stdin);
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));
    return 0;
}
