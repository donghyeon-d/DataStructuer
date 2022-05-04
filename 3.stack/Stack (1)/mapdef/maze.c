#include "mapdef.h"
#include <stdio.h>
#include <stdlib.h>

void    dirction_count(int mazeArray[HEIGHT][WIDTH], MapPosition *curPos)
{
    int count;

    count = 0;
    // 북쪽
    if (curPos->y && mazeArray[curPos->y - 1][curPos->x] == 0)
    	count++;
    if (curPos->x < WIDTH && mazeArray[curPos->y][curPos->x + 1] == 0)
		count++;
	// 남쪽
    if (curPos->y < HEIGHT && mazeArray[curPos->y + 1][curPos->x] == 0)
		count++;
	// 서쪽
    if (curPos->x && mazeArray[curPos->y][curPos->x - 1] == 0)
		count++;
    curPos->cnt = count;
}

void	get_direction(int mazeArray[HEIGHT][WIDTH], MapPosition *curPos)
{
	// 북쪽
	if (curPos->y && mazeArray[curPos->y - 1][curPos->x] == 0)
    	curPos->direction = NORTH;
	// 동쪽
    else if (curPos->x < WIDTH && mazeArray[curPos->y][curPos->x + 1] == 0)
		curPos->direction = EAST;
	// 남쪽
    else if (curPos->y < HEIGHT && mazeArray[curPos->y + 1][curPos->x] == 0)
		curPos->direction = SOUTH;
	// 서쪽
    else if (curPos->x && mazeArray[curPos->y][curPos->x - 1] == 0)
		curPos->direction = WEST;
	else
		curPos->direction = -1;
}

void	ft_move(int mazeArray[HEIGHT][WIDTH], MapPosition *curPos)
{
	mazeArray[curPos->y][curPos->x] = 2;
	if (curPos->direction == NORTH)
		curPos->y--;
	else if (curPos->direction == EAST)
		curPos->x++;
	else if (curPos->direction == SOUTH)
		curPos->y++;
	else
		curPos->x--;
}

void	popPath(MapStack *path, MapPosition savePos, MapPosition curPos)
{
	int			x;
	int			y;
	MapPosition	*temp;

	x = savePos.x - curPos.x;
    if (x < 0)
		x *= -1;
	y = savePos.y - curPos.y;
    if (y < 0)
		y *= -1;
	x += y;
	while (--x)
	{
		temp = popLS(path);
		free(temp);
	}
}

MapStack	*findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos)
{
	MapStack	*path;
	MapStack	*save;
	MapPosition	curPos;
	MapPosition *temp;

	path = createMapStack();
	save = createMapStack();
	curPos = startPos;
	get_direction(mazeArray, &curPos);
	dirction_count(mazeArray, &curPos);
	while (curPos.x != endPos.x || curPos.y != endPos.y)
	{
		// 막히고 세이브포인트 없음
		if (curPos.direction == -1 && isMapStackEmpty(save))
		{
			printf("can not find path!!!\n");
			deleteMapStack(path);
			deleteMapStack(save);
			return (NULL);
		}
		// 세이브 포인트로 이동
		else if (curPos.direction == -1)
		{
			temp = peekLS(save);
			temp->cnt--;
			popPath(path, *temp, curPos);
			mazeArray[curPos.y][curPos.x] = 2;
			curPos.x = temp->x;
			curPos.y = temp->y;
			get_direction(mazeArray, &curPos);
			if (temp->cnt == 1)
			{
				free (popLS(save));
				temp = NULL;				
			}
			ft_move(mazeArray, &curPos);
			get_direction(mazeArray, &curPos);
		}
		// 계속 진행
		else
		{
			pushLS(path, curPos);
	        dirction_count(mazeArray, &curPos);
	        if (curPos.cnt > 1)
	            pushLS(save, curPos);
	        ft_move(mazeArray, &curPos);
			get_direction(mazeArray, &curPos);
		}
	}
	mazeArray[curPos.y][curPos.x] = 2;
	printf("%d\n", curPos.direction);
	printf("Position{%d, %d}\n\n", curPos.x, curPos.y);
	deleteMapStack(save);
	return (path);
}

void	showPath(MapStack *path)
{
	MapPosition	*del;
	MapStack	*temp;
	int			i;
	
	temp = createMapStack();
	while (!isMapStackEmpty(path))
	{
		del = popLS(path);
		pushLS(temp, *del);
		free(del);
	}
	deleteMapStack(path);
	i = 0;
	while (!isMapStackEmpty(temp))
	{
		if (i == 5)
		{
			printf("\n");
			i = 0;
		}
		del = popLS(temp);
		printf("{%d, %d}->", del->x, del->y);
		free(del);
		i++;
	}
	printf("finish\n");
	deleteMapStack(temp);
}

void	printMaze(int mazeArray[HEIGHT][WIDTH])
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (mazeArray[y][x] == 1)
				printf("◼︎");
			else if (mazeArray[y][x] == 2)
				printf("O");
			else
				printf("+");
			if (x != WIDTH - 1)
				printf(" ");
			x++;
		}
		printf("\n");
		y++;
	}
}


int	main()
{
	MapStack	*path;
	// int mazeArray[HEIGHT][WIDTH] = {
    // {0, 0, 1, 1, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 1, 1, 0, 1, 1, 1, 1},
    // {1, 1, 1, 0, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 0, 1, 1, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 0},
    // {1, 1, 1, 1, 1, 1, 1, 0}
	// };
    int mazeArray[HEIGHT][WIDTH] = {
    {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
	};
	printMaze(mazeArray);
	printf("\n");
	path = findPath(mazeArray, (MapPosition){0, 0, 0, 0, NULL}, (MapPosition){11, 11, 0, 0, NULL});
	printMaze(mazeArray);
    system("leaks ")
	return 0;
}

// void	findPath(int mazeArray[HEIGHT][WIDTH], MapPosition startPos, MapPosition endPos, LinkedStack *pStack)
// {
//     if (startPos == endPos)//종료조건
//         pStack->complete = 1;
//     if (pStack->complete = 1)
//         return ;
//     while (4방향)
//     {
//         방향 더 해
//         if 더한거가 유효 범위 안에 없으면
//             지나가기
//         else if (방향 더한거가 0이면 고)
//             그 지점은 2로 만듬
//             pushLSMapPosition(pStack, startPos); //그 지점 푸시
//             findPath(mazeArray, 옮겨간 자리, endPos, pSatck);
//         방향++;
//     }
//     popStack;
// }

// HEIGHT 12
// WIDTH 12

// 	int mazeArray[HEIGHT][WIDTH] = {
//     {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
//     {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//     {0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
//     {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
//     {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
//     {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
//     {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
//     {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
// 	};

	// 8 x 8 start {0, 0} end {7, 7}
	// int mazeArray[HEIGHT][WIDTH] = {
    // {0, 0, 1, 1, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 1, 1, 0, 1, 1, 1, 1},
    // {1, 1, 1, 0, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 0, 1, 1, 1, 1, 1, 1},
    // {1, 0, 0, 0, 0, 0, 0, 0},
    // {1, 1, 1, 1, 1, 1, 1, 0}
	// };
	//	10x10 start {0, 1} end {9, 8}
	// int mazeArray[HEIGHT][WIDTH] = {
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// 	{0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	// 	{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 1, 1, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 0, 0, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	// 	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
	// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };
	// 12x12 start {0, 0} end {11, 11}
	// int mazeArray[HEIGHT][WIDTH] = {
    // {0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    // {0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    // {0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1},
    // {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    // {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
    // {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    // {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    // {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    // {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    // {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    // {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
	// };