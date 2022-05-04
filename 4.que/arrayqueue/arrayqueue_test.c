#include "arrayqueue.h"

int	main(void)
{
	ArrayQueue		*pQueue = createArrayQueue(15);
	ArrayQueueNode	element;
	
	element.data = 10;
	for (int i = 0; i < 15; i++)
	{
		enqueueAQ(pQueue, element);
		displayArrayQueue(pQueue);
		element.data += 10;
	}
	printf("len : %d\n", getArrayQueueLength(pQueue));
	// for (int i = 14; i >= 0 ; i--)
	// {
	// 	dequeueAQ(pQueue);
	// 	displayArrayQueue(pQueue);
	// }
	for (int i = 14; i >= 0 ; i--)
	{
		printf("%d\n", peekAQ(pQueue));
		dequeueAQ(pQueue);
	}
	printf("len : %d\n", getArrayQueueLength(pQueue));
	deleteArrayQueue(pQueue);
	system("leaks a.out | grep laeked");
}