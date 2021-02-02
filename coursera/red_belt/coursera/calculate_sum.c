#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() 
{
    int num;
    scanf("%d\n", &num);
    int *arr = (int*)malloc(num * sizeof(int));
    for( int i = 0; i != num ; ++i)
        scanf("%d ", &arr[i]);
    int sum = 0;
    for( int i = 0; i != num ; ++i)
        sum += arr[i];    
    printf("%d", sum);
    free(arr);
    return 0;
}
