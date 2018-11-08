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

    int line_number = -1;
    
    for (int i = 0; i < n && line_number == -1; ++i)
    {
        int all_zeros = 1;
        for (int j = 0; j < n && all_zeros; ++j)
            if (a[i][j] != 0) all_zeros = 0;
        if (all_zeros) line_number = i;
    }

    if (line_number == -1)
    {
        printf("No lines where all elements are zeros\n");
        system("pause");
        return 0;
    }

    for (int i = 0; i < n; ++i)
        a[i][line_number] /= 2;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%4d", a[i][j]);
        printf("\n");
    }

    system("pause");
    return 0;
}