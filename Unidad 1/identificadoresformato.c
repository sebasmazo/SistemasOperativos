#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char s[] = "an evil presence";
    printf("%s\n", s);
    printf("%7s\n", s);
    printf("%20s\n", s);
    printf("%-20s\n", s);
    printf("%.5s\n", s);
    printf("%.12s\n", s);
    printf("%15.12s\n", s);
    printf("%-15.12s\n", s);
    printf("%3.12s\n", s);
}