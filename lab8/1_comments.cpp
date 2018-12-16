#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Customer
{
    char   first_name[50]; // имя
    char    last_name[50]; // фамилия
    char     patronym[50]; // отчество
    char      address[50]; // адрес
    char phone_number[50]; // номер телефона
    char  card_number[50]; // номер карты
};


// прототипы функций
int  menu();                              // Печатает меню и возвращает результат
void add(struct Customer**, int*);        // добавляет нового покупателя
struct Customer read();                   // читает покупателя и возвращает структуру с ним
void sort(struct Customer*, int);         // сортирует массив
void search(struct Customer*, int);       // поиск по массиву
void change(struct Customer*, int);       // изменение одной записи
void remove(struct Customer**, int*);     // удаление записи
void print(struct Customer*, int);        // печатает весь массив
void print(struct Customer);              // печатает одну запись
void quit();                              // завершает программу

int main()
{
    struct Customer* customers = NULL; // указатель на массив с записями о покупателях. Пока что пустой
    int c_size = 0; // размер массива

    while (true)
    {
        switch (menu()) // выводим меню, получаем ответ
        {
            case 1:
                // Добавление нового пользователя
                add(&customers, &c_size);
                break;
            case 2:
                // сортировка массива
                sort(customers, c_size);
                break;
            case 3:
                // поиск по массиву
                search(customers, c_size);
                break;
            case 4:
                // изменение записи
                change(customers, c_size);
                break;
            case 5:
                // удаление записи
                remove(&customers, &c_size);
                break;
            case 6:
                // вывести всё
                print(customers, c_size);
                break;
            case 7:
                // выйти из программы
                quit();
                break;
            default:
                printf("Unknown command, try once again\n\n");
        }
    }
    return 0;
}

int menu() // печатаем меню, ничего сложного
{
    printf("\t1 - - - Add\n");
    printf("\t2 - - - Sort\n");
    printf("\t3 - - - Search\n");
    printf("\t4 - - - Change\n");
    printf("\t5 - - - Delete\n");
    printf("\t6 - - - Print\n");
    printf("\t7 - - - Quit\n");

    printf("Your choice > ");

    int choice;
    scanf_s("%d", &choice); // получаем ответ
    return choice; // и возвращаем
}

struct Customer read() // чтение новой записи о покупателе
{
    struct Customer nc; // создаём новую структуру
    printf("Name:\n");
    getc(stdin); // (опять с запарка с переводом строки, небольшой workaround)
    gets_s(nc.first_name, 49); // читаем имя
    printf("Last name:\n");
    gets_s(nc.last_name, 49); // фамилию (и т.д.)
    printf("Patronymic:\n");
    gets_s(nc.patronym, 49);
    printf("Address:\n");
    gets_s(nc.address, 49);
    printf("Phone number:\n");
    gets_s(nc.phone_number, 49);
    printf("Card number:\n");
    gets_s(nc.card_number, 49);
    return nc; // возвращаем запись
}

void add(struct Customer** c, int* sz) // добавление новой записи в массив
{
    *c = (struct Customer*) realloc(*c, sizeof(struct Customer) * (*sz + 1)); // увеличиваем размер массива на 1
    // для справки:
    /*
        void* realloc(void* ptr, size_t size);
        принимает: void* ptr - указатель на область памяти, которую нужно изменить
                   size_t size - новый размер (абсолютный)
        возвращает: void* указатель на область памяти с изменённым размером (поэтому нужно приводить тип)

        приведение типа                размер одной записи        новое кол-во записей
        (struct Customer*) realloc(*c, sizeof(struct Customer) * (*sz + 1))
    */
    (*sz)++; // увеличиваем переменную с размером массива

    (*c)[*sz - 1] = read(); // читаем в новое освободившееся место новую запись
    
    sort(*c, *sz); // сортим всё
}

void sort(struct Customer* c, int sz) // функция сортировки
{
    struct Customer buf; // временный буфер
    for (int i = 0 ; i < sz; ++i) 
        for (int j = i; j < sz - 1; ++j) // обычный пузырёк
        {
            if (strcmp(c[j].first_name, c[j + 1].first_name) > 0) // сравниваем, как в условии - первое поле записи
            {
                buf = c[j];
                c[j] = c[j + 1];
                c[j + 1] = buf;
            }
        }
}   

void search(struct Customer* c, int sz) // поиск по параметру
{
    int search_by = 0; // номер параметра для поиска
    do {                // читаем номер
        printf("Search by:\n");
        printf("\t1 - Name\n"); 
        printf("\t2 - Surname\n");
        printf("\t3 - Patronymic\n");
        printf("\t4 - Address\n");
        printf("\t5 - Phone number\n");
        printf("\t6 - Card number\n");
        printf("Your choice > ");
        scanf_s("%d", &search_by);
    } while (search_by < 1 || search_by > 6); // не прекратим читать, пока не введут нормальный номер

    printf("Search query:\n"); // читаем запрос для поиска
    char query[50]; // вот сюда его прочитаем
    getc(stdin); // хак с переводом строки
    gets_s(query, 49); // прочитали
    
    bool found = false; // флаг о том, что хоть что-то найдено
    for (int i = 0; i < sz; ++i) // идём по массиву
    {
        char* cmp; // это поле, с которым мы будем сравнивать текст из запроса
        switch (search_by) // заполняем это поля в зависимости от того, по какому полю мы ищем
        {
            case 1: // например, если ищем по имени
                cmp = c[i].first_name; // то сюда кладём имя из текущей записи
                break; // и так со всеми остальными полями
            case 2:
                cmp = c[i].last_name;
                break;
            case 3:
                cmp = c[i].patronym;
                break;
            case 4:
                cmp = c[i].address;
                break;
            case 5:
                cmp = c[i].phone_number;
                break;
            case 6:
                cmp = c[i].card_number;
                break;
            default:
                cmp = c[i].first_name;
        }
        
        if (strstr(cmp, query) != NULL) // теперь ищем вхождение строки из запроса в нашу строку
        {
            printf("#%d:\n", i); // если входит, то выводим
            print(c[i]);
            printf("\n----------\n");
            found = true; // и флаг поднимаем
        }
    }

    if (!found)
        printf("\nNo records found\n"); // если ничего не нашли, то так и скажем
}

void change(struct Customer* c, int sz) // изменяем запись
{
    int index; // номер записи, которую поменяем
    printf("Input number of element to change: ");
    scanf_s("%d", &index); // читаем его

    if (index >= sz) { // проверям, мб такой вообще нету (тут бы ещё на отрицательные чекнуть)
        printf("No such element\n");
        return;
    }

    printf("Old values:\n"); // выведем старые значения, на всякий случай, чтоб пользователь не запутался
    print(c[index]);

    printf("\n\nNew values:\n");
    c[index] = read(); // и прочитаем новые
    
    sort(c, sz); // посортим, чтоб норм всё было
}

void remove(struct Customer** c, int *sz) // удаление записи
{
    int index;
    printf("Input index to remove: ");
    scanf_s("%d", &index); // опять же, номер записи читаем и проверяем, что она существует
    if (index >= *sz)
    {
        printf("No such element\n");
        return;
    }

    for (int i = index; i < *sz - 1; ++i) // теперь пройдёмся от этой записи и до конца
    {
        (*c)[i] = (*c)[i + 1]; // и сдвинем на один все элементы, перетерев ту, которую хотим удалить.
    }

    *c = (struct Customer*) realloc(*c, sizeof(struct Customer) * (*sz - 1)); // теперь осталось удалить лишнюю последнюю
    (*sz)--; // и уменьшить размер массива
}

void print(struct Customer* c, int sz) // вывод всего массива
{
    for (int i = 0; i < sz; ++i) // ничего сверхъестественного
    {
        printf("#%d:\n", i);
        print(c[i]); // выводим текущий элемент
        printf("\n");
    }
}

void print(struct Customer c) // вывод одного элемента
{
    printf("Name: %s\n", c.first_name); // предельно просто
    printf("Surname: %s\n", c.last_name);
    printf("Patronymic: %s\n", c.patronym);
    printf("Address: %s\n", c.address);
    printf("Phone number: %s\n", c.phone_number);
    printf("Card number: %s", c.card_number);
}

void quit() // выход из программы
{
    exit(0);
}