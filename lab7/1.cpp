#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1(int***, int, int);
void task2();
void read_matrix(int***, int*, int*);
void print_matrix(int**, int, int);
void print_menu();

int main()
{
    int** matrix = NULL;
    int n = 0, m = 0; // matrix size

    while (true)
    {
        print_menu();
        int code;
        scanf_s("%d", &code);
        switch (code)
        {
            case 1: 
                read_matrix(&matrix, &n, &m);
                break;
            case 2:
                task1(&matrix, n, m);
                break;
            case 3:
                print_matrix(matrix, n, m);
                break;
            case 4:
                task2();
                break;
            case 5:
                for (int i = 0; i < n; ++i)
                    delete[] matrix[i];
                delete[] matrix;
                return 0;
        }
    }
    return 0;
}

void task1(int*** matrix, int n, int m)
{
    int line_number = -1;

    for (int i = 0; i < n && line_number == -1; ++i)
    {
        int all_zeros = 1;
        for (int j = 0; j < n && all_zeros; ++j)
            if ((*matrix)[i][j] != 0) all_zeros = 0;
        if (all_zeros) line_number = i;
    }

    if (line_number == -1)
    {
        printf("No lines where all elements are zeros\n");
        return;
    }

    if (line_number >= m)
    {
        printf("No column number %d\n", line_number + 1);
        return;
    }

    for (int i = 0; i < n; ++i)
        (*matrix)
[i][line_number] /= 2;
}

void task2()
{
    int n;
    printf("Number of lines: ");
    scanf_s("%d", &n);

    printf("Input text:\n");
    char** text = new char*[n];
    getc(stdin); // workaround
    for (int i = 0; i < n; ++i)
    {
        text[i] = new char[256];
        gets_s(text[i], 256);
    }

    printf("Symbol to search for: ");
    char c;
    scanf_s("%c", &c, 1);

    int counter = 0;
    for (int i = 0; i < n; ++i)
    {
        char* cur = text[i];
        while ((cur = strchr(cur, c)) != NULL)
        {
            counter++;
            cur++;
        }
    }
    printf("Number of occurrences of '%c' character: %d\n", c, counter);

    for (int i = 0; i < n; ++i)
        delete[] text[i];
    delete[] text;
}

void read_matrix(int*** matrix, int* pn, int* pm)
{
    if (*matrix != NULL)
    {
        for (int i = 0; i < *pn; ++i)
            delete[](*matrix)[i];
        delete[] *matrix;
    } // preventing memory leaks

    printf("Matrix size (N, M): ");
    scanf_s("%d %d", pn, pm);
    int n = *pn, m = *pm;

    *matrix = new int*[n];
    for (int i = 0; i < n; ++i)
        (*matrix)[i] = new int[m];
    
    printf("Input matrix line by line:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Line [%d]: ", i + 1);
        for (int j = 0; j < m; ++j)
            scanf_s("%d", &(*matrix)[i][j]);
    }
}

void print_matrix(int** matrix, int n, int m)
{
    printf("Matrix:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%4d", matrix[i][j]);
        printf("\n");
    }
}

void print_menu()
{
    printf("\t1 - - - New matrix\n");
    printf("\t2 - - - Task 1\n");
    printf("\t3 - - - Print matrix\n");
    printf("\t4 - - - Task 2\n");
    printf("\t5 - - - Quit\n");
}
