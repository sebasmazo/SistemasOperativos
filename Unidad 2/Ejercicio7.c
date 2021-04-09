//execDemo.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
    char *args[] = {"./EXEC", NULL};
    execv(args[0], args);
    printf("Ending-----");
    return 0;
}