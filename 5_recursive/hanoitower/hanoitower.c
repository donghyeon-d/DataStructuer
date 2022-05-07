#include "hanoitower.h"

void    hanoi_tower(int n, ArrayStack *from, ArrayStack *to, ArrayStack *temp)
{
    if (n < 1)
        return ;
    if (n == 1)
        pushAS(to, *(popAS(from)));
    else
    {
        hanoi_tower(n - 1, from, temp, to);
        pushAS(to, *(popAS(from)));
        hanoi_tower(n - 1, temp, to, from);
    }
}

int main()
{
    ArrayStack *from;
    ArrayStack *to;
    ArrayStack *temp;
    int         height;
    StackNode   layer;

    printf("input Height : ");
    scanf("%d", &height);

    from = createArrayStack(height);
    to = createArrayStack(height);
    temp = createArrayStack(height);
    layer.data = 0;

    while (layer.data < height)
    {
        pushAS(from, layer);
        // pushAS(to, layer);
        // pushAS(temp, layer);
        layer.data++;
    }

    printf("<--- before move --->\n");
    printf("[from] : "); displayArrayStack(from);
    printf("[to] : "); displayArrayStack(to);
    printf("[temp] : "); displayArrayStack(temp);

    printf("\n\n<--- after move --->\n");
    hanoi_tower(height, from, to, temp);
    printf("[from] : "); displayArrayStack(from);
    printf("[to] : "); displayArrayStack(to);
    printf("[temp] : "); displayArrayStack(temp);

}