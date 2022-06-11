#include <stdio.h>

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

void	quick_middle_pivot(int *arr, int left_idx, int right_idx)
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
void	quick_right_pivot(int *arr, int left_idx, int right_idx)
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
		// for (int i = 0; i < 8; i++)
		// 	printf("%d ", arr[i]);
		// printf("\n");
	}
	ft_swap(&arr[i], &arr[right_idx]);
	if (i > left_idx)
		quick(arr, left_idx, i - 1);
	if (i < right_idx)
		quick(arr, i + 1, right_idx);
}

void	quick_left_pivot(int *arr, int left_idx, int right_idx)
{
	int	i;
	int	j;
	int	pivot;

	i = left_idx;
	j = right_idx - 1;
	pivot = arr[left_idx];
	while(i < j)
	{
		while(arr[i] < pivot)
			i++;
		while(arr[j] > pivot)
			j--;
		if(i < j)
			ft_swap(&arr[i], &arr[j]);
	}
	ft_swap(&arr[j], &arr[right_idx]);
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

int main()
{

	int arr[10] = {6, 5, 8, 3, 7, 2, 4, 1};
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n");
	quick_01(arr, 0, 7);
	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
}