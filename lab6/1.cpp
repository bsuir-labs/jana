#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k;
    printf("Size: ");
    scanf_s("%d", &k);
    
    int *arr = new int[k];
    printf("Elements of array (k): ");
    for (int i = 0; i < k; ++i)
    {
        scanf_s("%d", arr + i);
    }

    int positive_cnt = 0, sum = 0;
    int zeros_cnt = 0;
    for (int i = 0; i < k; ++i)
    {
        sum += *(arr + i);
        if (*(arr + i) == 0)
        {
            zeros_cnt++;
            sum = 0;
        }

        if (*(arr + i) > 0) positive_cnt++;
    }

    printf("Number of positives: %d\n", positive_cnt);
    if (zeros_cnt > 0)
        printf("Sum of elements after the last zero: %d\n", sum);
    else
        printf("No zeros\n");

    delete[] arr;
    system("pause");
    return 0;
}