#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int max(int a, int b)
{
    return (a > b ? a : b);
}

int main()
{
    FILE* a, *b, *c; // объявляем указатели на файлы
    
    a = fopen("nameA.txt", "r"); // пытаемся их открыть
    b = fopen("nameB.txt", "r");
    c = fopen("nameC.txt", "r");

    if (a == NULL || b == NULL || c == NULL) // если ни один не открылся, просим нормально создать
    {
        printf("Create files properly!");

        system("pause");
        return 0;
    }

    FILE* d; // указатель на файл с результатом
    if ((d = fopen("nameD.txt", "w")) == NULL) // пытаемся создать, если не вышло - вылетаем
    {
        printf("Can't create new file, exiting\n");

        system("pause");
        return 0;
    }

    int x, y, z; // переменные для чтения чисел из каждого из файлов
    while (fscanf_s(a, "%d", &x) != EOF) // читаем из первого, до тех пор, пока файл не кончится (EOF - End Of File)
    {
        if (fscanf_s(b, "%d", &y) == EOF) // Читаем из второго. Если вдруг кончились числа (а в первом, если мы сюда зашли, они ещё есть)
        {                                   // значит, что-то не так, просим пересоздать файлы
            printf("Create files properly");
            system("pause");
            return 0;
        }
        if (fscanf_s(c, "%d", &z) == EOF) // аналогично с третьим
        {
            printf("Create files properly");
            system("pause");
            return 0;
        }

        fprintf_s(d, "%d\n", max(x, max(y, z))); // выводим в ответ результат
    }

    fclose(a); // закрываем все файлы
    fclose(b);
    fclose(c);
    fclose(d);

    system("pause");
    return 0;
}
