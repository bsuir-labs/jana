#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char FILENAME[] = "database.bin";

struct Customer
{
    char first_name[50];
    char last_name[50];
    char patronym[50];
    char address[50];
    char phone_number[50];
    char card_number[50];
};

int menu();
void add(struct Customer**, int*);
struct Customer read();
void sort(struct Customer*, int);
void search(struct Customer*, int);
void change(struct Customer*, int);
void remove(struct Customer**, int*);
void print(struct Customer*, int);
void print(struct Customer);
void quit();

// file functions
void read_file(struct Customer**, int*, const char*);
void save_to_file(struct Customer*, int, const char*);
void create_new(const char* filename);

int main()
{
    struct Customer* customers = NULL;
    int c_size = 0;

    read_file(&customers, &c_size, FILENAME);

    while (true)
    {
        switch (menu())
        {
        case 1:
            // add
            add(&customers, &c_size);
            break;
        case 2:
            sort(customers, c_size);
            break;
            // sort
        case 3:
            // search
            search(customers, c_size);
            break;
        case 4:
            // change
            change(customers, c_size);
            break;
        case 5:
            // delete
            remove(&customers, &c_size);
            break;
        case 6:
            // print
            print(customers, c_size);
            break;
        case 7:
            // quit
            save_to_file(customers, c_size, FILENAME);
            quit();
            break;
        default:
            printf("Unknown command, try once again\n\n");
        }
    }
    return 0;
}

int menu()
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
    scanf_s("%d", &choice);
    return choice;
}

struct Customer read()
{
    struct Customer nc;
    printf("Name:\n");
    getc(stdin);
    gets_s(nc.first_name, 49);
    printf("Last name:\n");
    gets_s(nc.last_name, 49);
    printf("Patronymic:\n");
    gets_s(nc.patronym, 49);
    printf("Address:\n");
    gets_s(nc.address, 49);
    printf("Phone number:\n");
    gets_s(nc.phone_number, 49);
    printf("Card number:\n");
    gets_s(nc.card_number, 49);
    return nc;
}

void add(struct Customer** c, int* sz)
{
    *c = (struct Customer*) realloc(*c, sizeof(struct Customer) * (*sz + 1));
    (*sz)++;

    (*c)[*sz - 1] = read();

    sort(*c, *sz);
}

void sort(struct Customer* c, int sz)
{
    struct Customer buf;
    for (int i = 0; i < sz; ++i)
        for (int j = i; j < sz - 1; ++j)
        {
            if (strcmp(c[j].first_name, c[j + 1].first_name) > 0)
            {
                buf = c[j];
                c[j] = c[j + 1];
                c[j + 1] = buf;
            }
        }
}

void search(struct Customer* c, int sz)
{
    int search_by = 0;
    do {
        printf("Search by:\n");
        printf("\t1 - Name\n");
        printf("\t2 - Surname\n");
        printf("\t3 - Patronymic\n");
        printf("\t4 - Address\n");
        printf("\t5 - Phone number\n");
        printf("\t6 - Card number\n");
        printf("Your choice > ");
        scanf_s("%d", &search_by);
    } while (search_by < 1 || search_by > 6);

    printf("Search query:\n");
    char query[50];
    getc(stdin);
    gets_s(query, 49);

    bool found = false;
    for (int i = 0; i < sz; ++i)
    {
        char* cmp;
        switch (search_by)
        {
        case 1:
            cmp = c[i].first_name;
            break;
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

        if (strstr(cmp, query) != NULL)
        {
            printf("#%d:\n", i);
            print(c[i]);
            printf("\n----------\n");
            found = true;
        }
    }

    if (!found)
        printf("No records found\n");
}

void change(struct Customer* c, int sz)
{
    int index;
    printf("Input number of element to change: ");
    scanf_s("%d", &index);

    if (index >= sz) {
        printf("No such element\n");
        return;
    }

    printf("Old values:\n");
    print(c[index]);

    printf("\n\nNew values:\n");
    c[index] = read();

    sort(c, sz);
}

void remove(struct Customer** c, int *sz)
{
    int index;
    printf("Input index to remove: ");
    scanf_s("%d", &index);
    if (index >= *sz)
    {
        printf("No such element\n");
        return;
    }

    for (int i = index; i < *sz - 1; ++i)
    {
        (*c)[i] = (*c)[i + 1];
    }

    *c = (struct Customer*) realloc(*c, sizeof(struct Customer) * (*sz - 1));
    (*sz)--;
}

void print(struct Customer* c, int sz)
{
    for (int i = 0; i < sz; ++i)
    {
        printf("#%d:\n", i);
        print(c[i]);
        printf("\n");
    }
}

void print(struct Customer c)
{
    printf("Name: %s\n", c.first_name);
    printf("Surname: %s\n", c.last_name);
    printf("Patronymic: %s\n", c.patronym);
    printf("Address: %s\n", c.address);
    printf("Phone number: %s\n", c.phone_number);
    printf("Card number: %s", c.card_number);
}

void quit()
{
    system("pause");
    exit(0);
}

void read_file(struct Customer** c, int *sz, const char* filename)
{
    FILE* file;
    if ((file = fopen(filename, "rb")) == NULL)
    {
        printf("Can't open file to read from. Check the existance of %s", filename);
        create_new(filename);
        return;
    }

    unsigned count;

    count = fread(sz, sizeof(int), 1, file);
    if (count < 1)
    {
        printf("Corrupted file. Creating new file...\n");
        fclose(file);
        create_new(filename);
        return;
    }

    *c = (struct Customer*) malloc(sizeof(struct Customer) * (*sz));

    for (int i = 0; i < *sz; ++i)
    {
        count = 0;
        count += fread((*c)[i].first_name, sizeof(char), 50, file);
        count += fread((*c)[i].last_name, sizeof(char), 50, file);
        count += fread((*c)[i].patronym, sizeof(char), 50, file);
        count += fread((*c)[i].address, sizeof(char), 50, file);
        count += fread((*c)[i].phone_number, sizeof(char), 50, file);
        count += fread((*c)[i].card_number, sizeof(char), 50, file);

        if (count != 50 * 6) {
            free(*c);
            fclose(file);
            create_new(filename);
            return;
        }
    }

    fclose(file);
}

void save_to_file(struct Customer* c, int sz, const char* filename)
{
    FILE* file;
    if ((file = fopen(filename, "wb")) == NULL)
    {
        printf("Can't open file to write to. Check the existance of %s", filename);
        create_new(filename);
    }

    fwrite(&sz, sizeof(int), 1, file);
    for (int i = 0; i < sz; ++i)
    {
        fwrite(c[i].first_name, sizeof(char), 50, file);
        fwrite(c[i].last_name, sizeof(char), 50, file);
        fwrite(c[i].patronym, sizeof(char), 50, file);
        fwrite(c[i].address, sizeof(char), 50, file);
        fwrite(c[i].phone_number, sizeof(char), 50, file);
        fwrite(c[i].card_number, sizeof(char), 50, file);
    }

    fclose(file);
}

void create_new(const char* filename)
{
    FILE* file;
    if ((file = fopen(filename, "w")) == NULL)
    {
        printf("Can't create new file, terminating.\n");
        quit();
    }
    printf("File %s has been successfully created\n", filename);
    fclose(file);
}