#include <stdio.h>

int preInoInt(int *n);
int postInoInt(int *n);

int main()
{
    int a = 2;

    printf("%d\n", preInoInt(&a));
    printf("%d\n", a);
    printf("%d\n", postInoInt(&a));
    printf("%d\n", a);

    return 0;
}

int preInoInt(int *n)
{
    return ++(*n);
}

int postInoInt(int *n)
{
    return (*n)++;    
}