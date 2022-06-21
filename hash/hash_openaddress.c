#include <stdlib.h>
#include <stdio.h>
#include "hash_openaddress.h"

t_hashTable *createHashTable(int maxCount)
{
    t_hashTable *newTable;

    newTable = malloc(sizeof(t_hashTable));
    newTable->maxCount = maxCount;
    newTable->currentCount = 0;
    newTable->used = calloc(maxCount, sizeof(int));
    newTable->hashTable = calloc(maxCount, sizeof(t_pair));
    return (newTable);
}

void	deleteHashTable(t_hashTable *table)
{
    free(table->used);
    free(table->hashTable);
    free(table);
}

int		isHashTableFull(t_hashTable *table)
{
	return (table->maxCount == table->currentCount);
}

int		isHashTableEmpty(t_hashTable *table)
{
    return (table->currentCount == 0);
}

int     isUsedIndex(t_hashTable *table, int index)
{
    return (table->used[index]);
}

int     pairCount(t_hashTable *table)
{
    return (table->currentCount);
}

int     ft_hashing(int maxCount, int key)
{
	int	index = key % maxCount;
	if (index < 0)
		index += maxCount;
    return(index);
}

int		addPair(t_hashTable *table, t_pair pair)
{
    if (isHashTableFull(table))
        return (FALSE);
    int index = ft_hashing(table->maxCount, pair.key);
	// 충돌발생
	if (table->used[index] == USE)
	{
		if (table->hashTable[index].key == pair.key)
		{
			table->hashTable[index].value = pair.value;
			return (TRUE);
		}
		// 충돌시 해결
		// 1. 선형 조사법
		// index = linearProbing_add(table, index, pair.key);
		// 2. 제곱 조사법
		// index = quadricProbing_add(table, index, pair.key);
		// 3. 이중 해싱
		index = DoubleProbing_add(table, index, pair.key);
		if (index < 0)
			return (FALSE);
	}
	table->hashTable[index] = pair;
    table->used[index] = USE;
    table->currentCount++;
	return (TRUE);
}

// 선형 조사법
int     linearProbing_add(t_hashTable *table, int index, int key)
{
    int newIndex;

    newIndex = (index + 1) % table->maxCount;
	while (newIndex < table->maxCount)
	{
        if (table->used[newIndex] == NOT_USED)
			return (newIndex);
		else if (table->used[newIndex] == USE && table->hashTable[newIndex].key == key)
		{
			table->currentCount--;
			return (newIndex);
		}
		newIndex = (newIndex + 1) % table->maxCount;
		if (newIndex == index)
			return (-1);
	}
	return(-1);
}

// 선형 조사법
int     linearProbing_del(t_hashTable *table, int index, int key)
{
    int newIndex;

    newIndex = (index + 1) % table->maxCount;
	while (newIndex < table->maxCount)
	{
        if (table->used[newIndex] == USE && table->hashTable[newIndex].key == key)
			return (newIndex);
		newIndex = (newIndex + 1) % table->maxCount;
		if (newIndex == index)
			return (-1);
	}
	return (-1);
}

// 제곱 조사법
int     quadricProbing_add(t_hashTable *table, int index, int key)
{
    int newIndex;
    int count;

    if (isHashTableFull(table))
        return (-1);
    count = 1;
	newIndex = (key + (count * count)) % table->maxCount;
    while (table->used[newIndex] == USE)
    {
        if (table->hashTable[index].key == key)
		{
			table->currentCount--;
			return (newIndex);
		}
        count++;
		if (count > table->maxCount)
			return (-1);
		newIndex = (key + (count * count)) % table->maxCount;
    }
    return (newIndex);
}

int     quadricProbing_del(t_hashTable *table, int index, int key)
{
    int newIndex;
    int count;

    if (isHashTableEmpty(table))
        return (-1);
    count = 1;
    newIndex = (index + count * count) % table->maxCount;
    while (table->used[newIndex] != NOT_USED && table->hashTable[newIndex].key != key)
    {
        count++;
		if (count > table->maxCount)
			return (-1);
        newIndex = (index + count * count) % table->maxCount;
    }
	if (table->used[newIndex] == NOT_USED)
        return (-1);
    return (newIndex);
}

static int	ft_is_prime(int nb)
{
	int	i;

	if (nb < 2)
		return (0);
	if (!(nb % 2) && nb != 2)
		return (0);
	i = 3;
	while (i * i < nb + 1)
	{
		if (nb % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

static int	ft_find_last_prime(int nb)
{
	int	prime;

	if (nb < 3)
		return (2);
	if (!(nb % 2))
		nb--;
	prime = 0;
	if (!ft_is_prime(nb))
	{
		while (!prime)
		{
			nb -= 2;
			prime = ft_is_prime(nb);
		}
	}
	return (nb);
}

int     DoubleProbing_add(t_hashTable *table, int index, int key)
{
    int newIndex;
    int step;
    int prevPrime;
	int	count = 1;

    if (isHashTableFull(table))
        return (-1);
	prevPrime = ft_find_last_prime(table->maxCount);
    step = prevPrime - (index % prevPrime);
    newIndex = (index + (count * step)) % table->maxCount;
    while (table->used[newIndex] == USE)
    {
		if (table->hashTable[index].key == key)
		{
			table->currentCount--;
			return (newIndex);
		}
        count++;
        newIndex = (index + (count * step)) % table->maxCount;
    }
    return (newIndex);
}

int     DoubleProbing_del(t_hashTable *table, int index, int key)
{
    int newIndex;
    int step;
    int prevPrime;
	int	count = 1;

	prevPrime = ft_find_last_prime(table->maxCount);
    step = prevPrime - (index % prevPrime);
    newIndex = (index + (count * step)) % table->maxCount;
    while (table->used[newIndex] != NOT_USED && table->hashTable[newIndex].key != key)
    {
        count++;
        newIndex = (index + (count * step)) % table->maxCount;
    }
	if (table->used[newIndex] == NOT_USED)
        return (-1);
    return (newIndex);
}

t_pair	*deletePair(t_hashTable *table, t_pair pair)//pop
{
    t_pair *pop;

    pop = malloc(sizeof(t_pair));
	if (isHashTableEmpty(table))
        return (NULL);
    int index = ft_hashing(table->maxCount, pair.key);
    // 충돌발생
	if (table->hashTable[index].key != pair.key)
	{
		// 충돌시 해결
		// 1. 선형 조사법 add, del
		// index = linearProbing_del(table, index, pair.key);
		// 2. 제곱 조사법 add, del
		// index = quadricProbing_del(table, index, pair.key);
		index = DoubleProbing_del(table, index, pair.key);
		// 3. 이중 해싱	 add, del
		if (index < 0)
			return (NULL);
	}
    table->used[index] = USED;
    table->currentCount--;
    *pop = table->hashTable[index];
	return (pop);
}

t_pair	*searchPair(t_hashTable *table, t_pair pair) // peek
{
    if (isHashTableEmpty(table))
        return (NULL);
    int index = ft_hashing(table->maxCount, pair.key);
    // 충돌발생
	if (table->hashTable[index].key != pair.key)
	{
		// 충돌시 해결
		// 1. 선형 조사법 add, del
		index = linearProbing_del(table, index, pair.key);
		// 2. 제곱 조사법 add, del
		index = quadricProbing_del(table, index, pair.key);
		// 3. 이중 해싱	 add, del
		index = DoubleProbing_del(table, index, pair.key);
		if (index < 0)
			return (NULL);
	}
	return (&table->hashTable[index]);
}

void	displayTable(t_hashTable *table)
{
	for (int i = 0; i < table->maxCount; i++)
		printf("{%d, %d}(%d)  ", table->hashTable[i].key, table->hashTable[i].value, table->used[i]);
	printf("\n");
}

int main()
{
	t_hashTable	*table = createHashTable(11);
	t_pair		pair1 = {1, 1};
	t_pair		pair3 = {3, 3};
	t_pair		pair8 = {8, 8};
	t_pair		pair13 = {13, 13};
	t_pair		pair18 = {18, 18};
	t_pair		pair23 = {23, 23};
	addPair(table, pair1);	displayTable(table);
	addPair(table, pair3);	displayTable(table);
	addPair(table, pair8);	displayTable(table);
	addPair(table, pair13);	displayTable(table);
	addPair(table, pair18);	displayTable(table);
	addPair(table, pair23);	displayTable(table);

	printf("========del========\n");
	// del
	deletePair(table, pair1);	displayTable(table);
	deletePair(table, pair8);	displayTable(table);
	deletePair(table, pair18);	displayTable(table);
	deletePair(table, pair3);	displayTable(table);
	// addPair(table, pair1);		displayTable(table);
	// addPair(table, (t_pair){1, 5}); displayTable(table);
	// addPair(table, (t_pair){18, 12}); displayTable(table);
	// addPair(table, (t_pair){18, 15}); displayTable(table);
}
