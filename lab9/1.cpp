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
    FILE* a, *b, *c;
    
    a = fopen("nameA.txt", "r");
    b = fopen("nameB.txt", "r");
    c = fopen("nameC.txt", "r");

    if (a == NULL || b == NULL || c == NULL)
    {
        printf("Create files properly!");

        system("pause");
        return 0;
    }

    FILE* d;
    if ((d = fopen("nameD.txt", "w")) == NULL)
    {
        printf("Can't create new file, exiting\n");

        system("pause");
        return 0;
    }

    int x, y, z;
    while (fscanf_s(a, "%d", &x) != EOF)
    {
        if (fscanf_s(b, "%d", &y) == EOF)
        {
            printf("Create files properly");
            system("pause");
            return 0;
        }
        if (fscanf_s(c, "%d", &z) == EOF)
        {
            printf("Create files properly");
            system("pause");
            return 0;
        }

        fprintf_s(d, "%d\n", max(x, max(y, z)));
    }

    fclose(a);
    fclose(b);
    fclose(c);
    fclose(d);

    system("pause");
    return 0;
}
