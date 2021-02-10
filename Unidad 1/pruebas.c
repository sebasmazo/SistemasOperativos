#include <stdio.h>
#include <unistd.h>

    void f1(int, int *, int *);

    int main()
    {
        int d1 = 3, d2 = 1, d3 = 4;
        printf("%d,%d,%d\n",d1,d2,d3);
        f1(--d2, &d3, &d1);
        print("%d,%d,%d\n", d1,d2,d3);
        return 0;
    }

    void f1(int x, int *y, int *z)
    {
        *y = x + *z;
        *z = --(*y);
        x = *y - *z;
    }
