#include <stdio.h>

int factorial(int n)
{
    int ret;

    ret = 0;
    if (n < 0)
        ret = -1;
    else if (n == 1 || n == 0)
        ret = 1;
    else
        ret = n * factorial(n - 1);
    return (ret);
}

int factorial_iter(int n)
{
    int ret;

    ret = 1;
    if (n < 0)
        ret = -1;
    else if (n == 1 || n == 0)
        ret = 1;
    else
    {
        while (n > 0)
        {
            ret *= n;
            n--;
        }
    }
    return (ret);
}

int main()
{
    int d;

    printf("input n : ");
    scanf("%d", &d);
    printf("recer : %d\n", factorial(d));
    printf("iter  : %d\n", factorial_iter(d));
}