#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int x, int y)
{
    return x > y ? x : y;
}

int main()
{
    int a[100][100];
    int n;
    printf("Size: ");
    scanf_s("%d", &n);

    printf("Input matrix:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Row #%d: ", i + 1);
        for (int j = 0; j < n; ++j)
            scanf_s("%d", &a[i][j]); 
    }

    for (int i = 0; i < n; ++i)
    {
        int current_product = 1, 
            no_negatives = 1;
        for (int j = 0; j < n && no_negatives; ++j)
        {
            if (a[i][j] < 0) no_negatives = 0;
            current_product *= a[i][j];
        }
        if (no_negatives)
        {
            printf("Row #%d has no negative numbers. ", i + 1);
            printf("The product of its elements: %d\n", current_product);
        }
    }

    int max_sum = -INT_MAX;
    for (int start = n - 1; start >= 0; --start)
    {
        int sum1 = 0,
            sum2 = 0;
        for (int i = start, j = 0; i < n; ++i, ++j)
            sum1 += a[i][j],
            sum2 += a[j][i];
        max_sum = max(max_sum, max(sum1, sum2));
    }

    printf("Max sum of diagonals: %d\n", max_sum);

    system("pause");
    return 0;
}