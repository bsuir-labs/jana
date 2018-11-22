#include <stdio.h>
#include <stdlib.h>

int main()
{
    int k; // количество элементов
    printf("Size: ");
    scanf_s("%d", &k);
    
    int *arr = new int[k]; // выделяем память на К элементов
    /*
        В теории у тебя почему-то написано про сишные функции malloc і т.п.,
        но в примере юзается С++ оператор new. В общем, эта строчка аналогична 
        строке int *arr = (int*) malloc((size_t) k); (size_t это тіп такой)
    */
    printf("Elements of array (k): ");
    for (int i = 0; i < k; ++i)
    {
        scanf_s("%d", arr + i); // читаем массив, в теории описано, что строка
    }                          // arr + i аналогічна строке &arr[i]

    int positive_cnt = 0, sum = 0; // кол-во положительных, сумма после нуля
    int zeros_cnt = 0; // количество нулей (вдруг их вообще нет и тогда никакой суммы тоже не будет)
    for (int i = 0; i < k; ++i)
    {
        sum += *(arr + i); // увеличиваем сумму
        if (*(arr + i) == 0) // если вдруг попали на ноль, обнулимся
        {
            zeros_cnt++; // и посчитаем этот ноль.
            sum = 0;
        }

        if (*(arr + i) > 0) positive_cnt++; // если число положительное, увеличиваем и этот счётчик
    }


    // выводим ответы
    printf("Number of positives: %d\n", positive_cnt);
    if (zeros_cnt > 0)
        printf("Sum of elements after the last zero: %d\n", sum);
    else
        printf("No zeros\n");

    delete[] arr; // очищаем память (не обязательно в данном случае, т.к. программа уже завершена
                    // и память и так освободится)
    system("pause");
    return 0;
}