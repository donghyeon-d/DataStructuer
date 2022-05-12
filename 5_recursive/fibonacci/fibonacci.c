#include <stdio.h>
#include <stdlib.h>

int fibonaccic(int n)
{
    int ret;

    if (n <= 0)
        ret = 0;
    else if (n == 1 || n == 2)
        ret = 1;
    else
        ret = fibonaccic(n - 2) + fibonaccic(n - 1);
    return (ret);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("input n");
    else
    printf("%d", fibonaccic(atoi(argv[1])));
        return (0);
}