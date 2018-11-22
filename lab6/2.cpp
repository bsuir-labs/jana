#include <stdio.h>
#include <stdlib.h>

int max(int x, int y)
{
    return x > y ? x : y;
}

int main()
{
    int n;
    printf("Size (N): ");
    scanf_s("%d", &n);

    int **matrix = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new int[n];
    }

    printf("Input matrix:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Row #%d: ", i + 1);
        for (int j = 0; j < n; ++j)
        {
            scanf_s("%d", *(matrix + i) + j);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        int current_product = 1,
            no_negatives = 1;
        for (int j = 0; j < n && no_negatives; ++j)
        {
            if (*(*(matrix + i) + j) < 0) no_negatives = 0;
            current_product *= *(*(matrix + i) + j);
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
            sum1 += *(*(matrix + i) + j),
            sum2 += *(*(matrix + j) + i);
        max_sum = max(max_sum, max(sum1, sum2));
    }

    printf("Max sum of diagonals: %d\n", max_sum);

    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
    
    system("pause");
    return 0;
}