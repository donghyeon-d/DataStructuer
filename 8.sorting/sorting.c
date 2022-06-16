#include <stdio.h>
#include <stdlib.h>
#include "../4.que/linkedqueue/linkedqueue_dongchoi.c"

// #define MAX_SIZE 10

// int buf[MAX_SIZE];

void ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	select(int *arr, int len)
{
	int min;
	int idx;

	for (int i = 0; i < len; i++)
	{
		min = arr[i];
		for(int j = i + 1; j < len; j++)
		{
			if(arr[j] < min)
			{
				min = arr[j];
				idx = j;
			}
		}
		ft_swap(&arr[i], &arr[idx]);
	}
}

void	bubble(int *arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				ft_swap(&arr[j], &arr[j + 1]);
		}
	}
}

void	quick(int *arr, int left_idx, int right_idx)
{
	int	i;
	int	j;
	int	pivot;

	i = left_idx;
	j = right_idx;
	pivot = arr[(right_idx + left_idx) / 2] ;
	while(i < j)
	{
		while(arr[i] < pivot)
			i++;
		while(arr[j] > pivot)
			j--;
		ft_swap(&arr[i], &arr[j]);
	}
	if (i > left_idx)
		quick(arr, left_idx, i - 1);
	if (i < right_idx)
		quick(arr, i + 1, right_idx);
}

void	quick_rightpivot(int *arr, int left_idx, int right_idx)
{
	int	i;
	int	j;
	int	pivot;

	i = left_idx;
	j = right_idx - 1;
	pivot = arr[right_idx];
	while(i < j)
	{
		while(arr[i] < pivot)
			i++;
		while(arr[j] > pivot)
			j--;
		if(i < j)
			ft_swap(&arr[i], &arr[j]);
		for (int i = 0; i < 8; i++)
			printf("%d ", arr[i]);
		printf("\n");
	}
	ft_swap(&arr[i], &arr[right_idx]);
	if (i > left_idx)
		quick(arr, left_idx, i - 1);
	if (i < right_idx)
		quick(arr, i + 1, right_idx);
}

void	insertion(int *arr, int len)
{
	int idx;
	int	tmp;

	for(int i = 1; i < len ; i++)
	{
		idx = i;
		tmp = arr[idx];
		for(int j = 0; j < i; j++)
		{
			if(arr[i] < arr[i - j - 1])
				idx--;
		}
		for(int k = i; k > idx; k--)
		{
			arr[k] = arr[k - 1];	
		}
		arr[idx] = tmp;
	}
}

static void	shell_util(int *arr, int len, int gap, int start)
{
	int idx;
	int tmp;

	for(int i = start + gap; i < len ; i += gap)
	{
		idx = i;
		tmp = arr[idx];
		for(int j = start; j <= i; j += gap)
		{
			if(arr[i] < arr[i - j])
				idx -= gap;
		}
		for(int k = i; k > idx; k -= gap)
		{
			arr[k] = arr[k - gap];
		}
		arr[idx] = tmp;
	}
}

void	shell(int *arr, int len)
{
	int	gap;
	int	i;

	gap = len / 2;
	if (gap % 2 == 0)
		gap++;
	while (gap > 0)
	{
		for (int i = 0; i < gap; i++)
		{
			if (i + gap > len - 1)
				break ;
			shell_util(arr, len, gap, i);// gap 으로 나눈 부분집집합 1개 삽입정렬
		}
		gap /= 2;
		if (gap != 0 && gap % 2 == 0)
			gap++;
	}
}

void	merge(int *arr, int *buf, int left, int right)
{
	int	mid;
	int arr_idx;
	int left_start;
	int right_start;

	mid = (left + right) / 2;
	arr_idx = left;
	left_start = left;
	right_start = mid + 1;
	while (left_start <= mid && right_start <= right)
	{
		if (arr[left_start] < arr[right_start])
		{
			buf[arr_idx++] = arr[left_start];
			left_start++;
		}
		else
		{
			buf[arr_idx++] = arr[right_start];
			right_start++;
		}
	}
	if (left_start == mid + 1)
	{
		while (right_start <= right)
		{
			buf[arr_idx] = arr[right_start];
			arr_idx++;
			right_start++;
		}
	}
	if (right_start == right + 1)
	{
		while (left_start <= mid)
		{
			buf[arr_idx] = arr[left_start];
			arr_idx++;
			left_start++;
		}
	}
	for (int i = left; i <= right; i++)
		arr[i] = buf[i];
}

void	divide(int *arr, int *buf, int len, int start, int end)
{
	int mid_idx;
	int	left;
	int	right;

	if(end - start < 1)
		return ;
	mid_idx = (start + end) / 2;
	left = start;
	right = end;
	divide(arr, buf, len, left, mid_idx); // 왼쪽 
	divide(arr, buf, len, mid_idx + 1, right); // 오른쪽
	merge(arr, buf, left, right);
}

void	radix(int *arr, int len)
{
	LinkedQueue *queue[10];
	int max;
	int digit;
	int tens;
	int	idx;
	LinkedQueueNode *element;

	for (int i = 0; i < 10; i++)
		queue[i] = createLinkedQueue();
	max = -2147483648;
	for (int j = 0; j < len; j++)
	{
		if (arr[j] > max)
			max = arr[j];
	}
	// digit = 0;
	// while (max > 0)
	// {
	// 	digit++;
	// 	max /= 10;
	// }
	tens = 10;
	while(tens <= max * 10)
	{
		idx = 0;
		for (int j = 0; j < len; j++)
		{
			element = malloc(sizeof(LinkedQueueNode));
			element->data = arr[j];
			element->pLink = NULL;
			enqueueLQ(queue[arr[j] % tens * 10 / tens], element);
			free(element);
		}
		int	k = 0;
		while (k < len)
		{
			element = dequeueLQ(queue[idx]);
			if(!element)
				idx++;
			else
				arr[k++] = element->data;
			if(element)
			{			
				free(element);
				element = NULL;
			}
		}
		tens *= 10;
	}
}

void	ft_heapsort(int *arr, int len)
{
	int idx;

	//heap 모양으로 만들어줌
	for (int i = 1; i < len; i++)
	{
		idx = i;
		while (idx > 0 && arr[idx] > arr[(idx - 1) / 2])
		{
			ft_swap(&arr[idx], &arr[(idx - 1) / 2]);
			idx = (idx - 1) / 2;
		}
	}
	// 바꿔주고 0번째 있는 원소를 자식과 비교하면서 바꿔주며 maxheap으로 만듦
	while (len > 0)
	{
		ft_swap(&arr[0], &arr[len - 1]);
		idx = 0;
		len--;
		while (idx < len - 1 && idx * 2 + 2 <= len - 1)
		{
			if (arr[idx] < arr[idx * 2 + 1] && arr[idx * 2 + 1] > arr[idx * 2 + 2])
			{
				ft_swap(&arr[idx], &arr[idx * 2 + 1]);
				idx = idx * 2 + 1;
			}
			else if (arr[idx] < arr[idx * 2 + 2])
			{
				ft_swap(&arr[idx], &arr[idx * 2 + 2]);
				idx = idx * 2 + 2;
			}
		}
	}
}

int main()
{
	int buf[10];
	int arr[10] = {612, 51, 84215, 32, 75, 2, 4, 1};
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");
	ft_heapsort(arr, 8);
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
}
