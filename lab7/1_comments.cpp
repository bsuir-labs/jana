#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void task1(int***, int, int); // прототипы функций. Зачем они нужны в теории норм написано вроде
void task2(); // тут не буду расписывать. Определения функций будут после main
void read_matrix(int***, int*, int*);
void print_matrix(int**, int, int);
void print_menu();

int main()
{
    int** matrix = NULL; // собственно, матрица
    int n = 0, m = 0; // и её размеры (высота и ширина)

    while (true) // бесконечный цикл программы
    {
        print_menu(); // выводим меню
        int code; // читаем выбор пользователя
        scanf_s("%d", &code);
        switch (code) // в зависимости от значения code выбираем наше действие
        { // (конструкция switch (x) {case...} аналогична if (x == 1) {} else if (x == 2) {} else ...)
            case 1:  // если выбрали вариант 1
                read_matrix(&matrix, &n, &m); // читаем матрицу
                break; // выходим из switch
            case 2:
                task1(&matrix, n, m); // выполняем задание 1
                break;
            case 3:
                print_matrix(matrix, n, m); // выводим матрицу
                break;
            case 4:
                task2(); // выполняем задание 2
                break;
            case 5:
                for (int i = 0; i < n; ++i) // удаляем матрицу (тут особой необходимости нет - программа завершается)
                    delete[] matrix[i]; // (но просто, чтоб привыкать подчищать память за собой)
                delete[] matrix;
                return 0; // выходим из программы
        }
    }
    return 0;
}

void task1(int*** matrix, int n, int m) // первое задание
{
    /*
        По сути, такое же задание у тебя было в одной из предыдущих лаб
        Единственное отличие, что здесь матрица передаётся по указателю
        Так что вместо matrix[i][j] пришлось писать (*matrix)[i][j]
    */
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
        (*matrix)[i][line_number] /= 2;
}

void task2() // второе задание. Здесь нам ничего не надо из основной программы, поэтому ф-ция не принимает аргументов
{
    int n; // кол-во строк в тексте
    printf("Number of lines: ");
    scanf_s("%d", &n);

    printf("Input text:\n");
    char** text = new char*[n]; // массив для текста (каждый элемент массива - отдельная строка)
    getc(stdin); // пришлось написать, чтобы перевести строку после Input text
    for (int i = 0; i < n; ++i) // читаем n строк
    {
        text[i] = new char[256]; // выделяем память на 256 символов (надеюсь, у тебя строки не будут длиннее)
        gets_s(text[i], 256); // читаем туда всю строку
    }

    printf("Symbol to search for: ");
    char c; // символ, который будем искать
    scanf_s("%c", &c, 1);

    int counter = 0; // количество встречаний такого символа в тексте
    for (int i = 0; i < n; ++i) // идём по каждой строке
    {
        /*
            Функция strchr(ptr, symbol) возвращает указатель на первую позицию
            символа symbol в строке (массиве символов - указателе), начинающемся с ptr.
        */
        char* cur = text[i]; // изначально указатель стоит на начале строки
        while ((cur = strchr(cur, c)) != NULL) // пока нам не вернётся NULL (значит, что символа такого нету)
        {
            counter++; // увеличиваем счётчик
            // в cur после 105-ой строчки лежит указатель на первый искомый символ в строке.
            cur++; // поэтому, чтобы ещё раз его не посчитать, сдвигаемся на один дальше
        }
    } // повторяем для всех строк
    printf("Number of occurrences of '%c' character: %d\n", c, counter);

    for (int i = 0; i < n; ++i) // удаляем текст из памяти (тут обязательно)
        delete[] text[i]; // иначе после выполнения функции указатели удалятся, а вот память будет занята
    delete[] text; // такое называется "утечкой памяти"
}

void read_matrix(int*** matrix, int* pn, int* pm) // ф-ция для чтения матрицы
{
    if (*matrix != NULL) // если у нас уже была какая-то матрица, нужно её удалить
    { // опять же, чтобы избежать утечек памяти
        for (int i = 0; i < *pn; ++i)
            delete[](*matrix)[i];
        delete[] *matrix;
    } 

    printf("Matrix size (N, M): ");
    scanf_s("%d %d", pn, pm); // читаем новый размер. pn и pm указывают на переменные n и m соответственно, находящиеся в main, сразу туда іх і прочтём
    int n = *pn, m = *pm; // для удобства введём n и m в текущей функции

    *matrix = new int*[n]; // выделяем память на новую матрицу
    for (int i = 0; i < n; ++i)
        (*matrix)[i] = new int[m];
    
    printf("Input matrix line by line:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("Line [%d]: ", i + 1);
        for (int j = 0; j < m; ++j)
            scanf_s("%d", &(*matrix)[i][j]); // и читаем её построчно
    }
}

void print_matrix(int** matrix, int n, int m) // печатаем на экран матрицу, ничего сложного
{
    printf("Matrix:\n");
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%4d", matrix[i][j]);
        printf("\n");
    }
}

void print_menu() // печатаем меню, ещё проще
{
    printf("\t1 - - - New matrix\n");
    printf("\t2 - - - Task 1\n");
    printf("\t3 - - - Print matrix\n");
    printf("\t4 - - - Task 2\n");
    printf("\t5 - - - Quit\n");
}
