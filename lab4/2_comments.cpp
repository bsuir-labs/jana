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

    printf("Input matrix:\n"); // ввод такой же как в первом задании
    for (int i = 0; i < n; ++i)
    {
        printf("Row #%d: ", i + 1);
        for (int j = 0; j < n; ++j)
            scanf_s("%d", &a[i][j]); 
    }

    int line_number = -1; // номер первой строки, где все нули
                          // если у нас в итоге останется -1, значит такой строки вообще нет
    
    for (int i = 0; i < n && line_number == -1; ++i) // идём по строкам, в условии смотрим, мб мы уже нашли 
    {                                                // строку, где только нули
        int all_zeros = 1; // флаг, что у нас одни нули. Аналогичный механизм в прошлом задании юзали
        for (int j = 0; j < n && all_zeros; ++j) // идём по строке
            if (a[i][j] != 0) all_zeros = 0; // если вдруг не ноль, опускаем флаг
        if (all_zeros) line_number = i; // если нашли строку, где одни нули - запоминаем номер
    }

    if (line_number == -1) // если такой строки нету, то вылетаем из программы
    {
        printf("No lines where all elements are zeros\n");
        system("pause");
        return 0;
    }

    for (int i = 0; i < n; ++i) // иначе делим все элементы в столбце с таким же номером на 2
        a[i][line_number] /= 2;

    for (int i = 0; i < n; ++i) // вы восхитительны
    {
        for (int j = 0; j < n; ++j)
            printf("%4d", a[i][j]);
        printf("\n");
    }

    system("pause");
    return 0;
}