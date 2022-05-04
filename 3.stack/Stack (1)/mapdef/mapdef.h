#ifndef _MAP_DEF_
#define _MAP_DEF_

#define WIDTH 12
#define HEIGHT 12

#define NUM_DIRECTIONS 4

enum compass {NORTH = 0, EAST, SOUTH, WEST};

enum PosStatus { NOT_VISIT = 0, WALL = 1 , VISIT = 2  };

typedef struct MapPositionType
{
	int x;
	int y;
	int direction;
	int cnt;
	struct MapPositionType *pLink;
} MapPosition;

typedef struct MapStack
{
	int currentElementCount;
	MapPosition* pTopElement;
} MapStack;

// offset: x, y
static int DIRECTION_OFFSETS[NUM_DIRECTIONS][2] = {
	{0, -1},		// 북
	{1, 0},			// 동
	{0, 1},			// 남
	{-1, 0}			// 서
};


MapStack* createMapStack();
int pushLS(MapStack* pStack, MapPosition element);
MapPosition* popLS(MapStack* pStack);
MapPosition* peekLS(MapStack* pStack);
void deleteMapStack(MapStack* pStack);
int isMapStackEmpty(MapStack* pStack);
void displayMapStack(MapStack* pList);
void print_line(char *str);


void    dirction_count(int mazeArray[HEIGHT][WIDTH], MapPosition *curPos);
void	popPath(MapStack *path, MapPosition temp, MapPosition curPos);
void	printMaze(int mazeArray[HEIGHT][WIDTH]);

// MapPosition	copyPosition(MapPosition *curPos);

#endif

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0
#define ERROR		-1

#endif


//유니코드 출력방법 \u0000