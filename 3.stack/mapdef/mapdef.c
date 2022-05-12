#include "mapdef.h"
#include "linkedstack.h"

int mazeArray[HEIGHT][WIDTH] = {
    {0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
}

void	printMaze(int mazeArray[HEIGHT][WIDTH])
{
    int h;
    int w;

    h = 0;
    while (h < HEIGHT)
    {
        w = 0;
        while (w < WIDTH)
        {
            printf("%d", mazeArray[h][w]);
            if (w != WIDTH - 1)
                printf(" ");
            w++;
        }
        printf("\n");
        h++;
    }
}

void	findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack)
{
    if (startPos == endPos)//종료조건
        pStack->complete = 1;
    if (pStack->complete = 1)
        return ;
    while (4방향)
    {
        방향 더 해
        if 더한거가 유효 범위 안에 없으면
            지나가기
        else if (방향 더한거가 0이면 고)
            그 지점은 2로 만듬
            pushLSMapPosition(pStack, startPos); //그 지점 푸시
            findPath(mazeArray, 옮겨간 자리, endPos, pSatck);
        방향++;
    }
    popStack;
}

void showPath(LinkedStack *pStack, int mazeArray[HEIGHT][WIDTH])
{
    pStack에 쌓여있는 data 의 index 들로 mazeArray의 각 자리들에 2를 넣어줌
    printMaze(mazeArray);
}

int main()
{
    MapPosition startPos;
    MapPosition endPos;
    enum PosStatus direction;
    LinkedStack *pStack;

    startPos = {0, 0, 0};
    endPos = {7, 7, 2};
    pStack = createLinkedStack();
}