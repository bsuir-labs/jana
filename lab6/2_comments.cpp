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

    // двумерный массив, это собственно массив массивов, т.е. в каждом элементе a[i] лежіт ещё массив.
    int **matrix = new int*[n]; // выдеяем память под массів массівов
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new int[n]; // и теперь выделяем по массиву на каждый элемент
    } // у нас получилась матрица, мы великолепны

    printf("Input matrix:\n"); // теперь прочитаем
    for (int i = 0; i < n; ++i)
    {
        printf("Row #%d: ", i + 1);
        for (int j = 0; j < n; ++j)
        {                                       // функция scanf со спеціфікатором %d принимает аргумент типа int*
                                                // matrix імеет тіп int**
            scanf_s("%d", *(matrix + i) + j); // *(matrix + i) сдвигает наш указатель на i строк и имеет тип int*
        }                                       // остаётся только сдвінуть на j столбцов. Итого наше выражение - *(matrix + i) + j
    }                                           // аналогічно запісі &matrix[i][j]

    for (int i = 0; i < n; ++i)
    {
        int current_product = 1,// начальное произведение (т.к. любое х * 1 = х)
            no_negatives = 1; // флаг, что в текущей строке нету отрицательных чисел. 
                              // если попадётся отрицательное, мы сюда положим 0
        for (int j = 0; j < n && no_negatives; ++j)  // идём по текущей строке. в условии также есть флаг
        {                                           // для того, чтобы мы остановились, как только найдём отрицательное число
            if (*(*(matrix + i) + j) < 0) no_negatives = 0; // если текущее меньше нуля - опускаем флаг
            current_product *= *(*(matrix + i) + j);// домножаем произведение на текущий элемент
        }
        if (no_negatives)// если у нас за всю строку так и не нашлось отрицательных, выводим ответ
        {
            printf("Row #%d has no negative numbers. ", i + 1);
            printf("The product of its elements: %d\n", current_product);
        }
    }

    /*
        По сути, тут и комментировать нечего, т.к. всё то же самое, что и в лабе про двумерные матрицы
        единственное отличие - доступ к элементам матрицы "через указатели", как выразились в твоей методе.
        В строке 40 (if (*(*(matrix + i) + j) < 0) no_negatives = 0;) я использую такой доступ.
        Для сравнения с числом (в данном случае - с нулём), нужно, чтобы элемент был типа int.
        matrix імеет тіп int**
        *(matrix + i)  - уже знаешь, объяснял чуть выше, имеет тип int*
        *(matrix + i) + j  - сдвігает на j столбцов и имеет тип int*. 
        нам нужно ізбавіться от этой звёздочкі, т.е. разыменовать указатель.
        поэтому: *(*(matrix + i) + j)
        аналогично записи matrix[i][j]
    */

    int max_sum = -INT_MAX; // начальное значение максимальной суммы
    /*
        Для удобства будем сразу по две диагонали проверять.
        Будем перебирать номер строки (а для второй диагонали - столбца),
        с которой начнётся наша текущая диагональ. Сразу посчитаем две суммы
        и положим в ответ максимальную из них.

        Пример. Матрица 5х5.
        "Первую диагональ" я возьму в круглые скобки, а вторую - в квадратные

        такие будут диагонали, если start == 2
         1   2  [3]  4   5
         6   7   8  [9]  1
        (2)  3   4   5  [6]
         7  (8)  9   0   1
         2   3  (4)  5   6
    */
    for (int start = n - 1; start >= 0; --start)// перебираем номер строки или столбца первого элемента
    {
        int sum1 = 0,// сумма для первой диагонали ()
            sum2 = 0; // сумма для второй диагонали []
        for (int i = start, j = 0; i < n; ++i, ++j)// идём по диагоналям. 
            sum1 += *(*(matrix + i) + j),// текущий элемент первой диагонали
            sum2 += *(*(matrix + j) + i);// текущий элемент второй диагонали
        max_sum = max(max_sum, max(sum1, sum2)); // обновляем ответ
    }

    printf("Max sum of diagonals: %d\n", max_sum);

    for (int i = 0; i < n; ++i)
        delete[] matrix[i];
    delete[] matrix;
    
    system("pause");
    return 0;
}