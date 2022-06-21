#include "hash_chaining.h"
#include <stdio.h>
#include <stdlib.h>

t_hashTable *createHashTable(int maxCount)
{
    t_hashTable *newTable;

    newTable = malloc(sizeof(t_hashTable));
    newTable->maxCount = maxCount;
    newTable->currentCount = 0;
    newTable->hashTable = calloc(maxCount, sizeof(t_pair));
    return (newTable);
}

void	deleteHashTable(t_hashTable *table)
{
	t_pair	*temp;
    t_pair	*del;

	for(int i = 0; i < table->maxCount; i++)
	{
        temp = table->hashTable[i].next;
        while (temp)
		{
			del = temp;
			temp = temp->next;
			free(del);
		}
	}
	free(table->hashTable);
	free(table);
}

int		isHashTableEmpty(t_hashTable *table)
{
    return (table->currentCount == 0);
}

int     pairCount(t_hashTable *table)
{
	return (table->currentCount);
}

int     ft_hashing(int maxCount, int key) //mod
{
	int	index = key % maxCount;
	if (index < 0)
		index += maxCount;
    return(index);
}

int		addPair(t_hashTable *table, t_pair pair)
{
    int idx = ft_hashing(table->maxCount, pair.key);
	t_pair	*temp;
    t_pair  *add = malloc(sizeof(t_pair));
    *add = pair;

	if (!table->hashTable[idx].next)
	{
		table->hashTable[idx].next = add;
		table->currentCount++;
		return (TRUE);
	}
	temp = table->hashTable[idx].next;
	while (temp)
	{
		if (temp->key == add->key)
		{
			temp->value = add->value;
			free(add);
			return (TRUE);
		}
        if (temp->next == NULL)
            break ;
		temp = temp->next;
	}
	temp->next = add;
	table->currentCount++;
	return (TRUE);
}

t_pair	*deletePair(t_hashTable *table, t_pair pair) // pop
{
	int idx = ft_hashing(table->maxCount, pair.key);
	t_pair	*temp = table->hashTable[idx].next;
	t_pair	*prev = table->hashTable[idx].next;
    
    if (isHashTableEmpty(table))
        return (NULL);
	if (temp->key == pair.key)
	{
		table->hashTable[idx].next = temp->next;
		table->currentCount--;
		temp->next = NULL;
		return (temp);
	}
	temp = temp->next;
	while (temp)
	{
		if (temp->key == pair.key)
        {
			prev->next = temp->next;
			table->currentCount--;
			temp->next = NULL;
			break ;
		}
        prev = prev->next;
		temp = temp->next;
	}
	return (temp);
}

t_pair	*searchPair(t_hashTable *table, t_pair pair) // peek
{
	int idx = ft_hashing(table->maxCount, pair.key);
	t_pair	*temp = table->hashTable[idx].next;
    
    if (isHashTableEmpty(table))
        return (NULL);
	while (temp && temp->key != pair.key)
		temp = temp->next;
	return (temp);
}

void	displayTable(t_hashTable *table)
{
    t_pair *temp;
	for (int i = 0; i < table->maxCount; i++)
    {
        temp = table->hashTable[i].next;
		printf("%d-> ", i);
        if (temp == NULL)
            printf("NULL");
        while (temp)
        {
            printf("{%d, %d} ", temp->key, temp->value);
            temp = temp->next;
        }
		printf("\n");
    }
	printf("\n");
}

int main()
{
    t_hashTable	*table = createHashTable(5);
	// t_pair		pair1 = {1, 1};
	t_pair		pair3 = {3, 3};
	t_pair		pair8 = {8, 8};
	t_pair		pair13 = {13, 13};
	t_pair		pair18 = {18, 18};
	t_pair		pair23 = {23, 23};

    // addPair(table, pair1);	displayTable(table);
	addPair(table, pair3);	displayTable(table);
	addPair(table, pair8);	displayTable(table);
	addPair(table, pair13);	displayTable(table);
	addPair(table, pair18);	displayTable(table);
	addPair(table, pair23);	displayTable(table);

	printf("========del========\n");
	// del
	// deletePair(table, pair1);	displayTable(table);
	deletePair(table, pair8);	displayTable(table);
	deletePair(table, pair18);	displayTable(table);
	deletePair(table, pair3);	displayTable(table);
	// addPair(table, pair1);		displayTable(table);
	addPair(table, (t_pair){1, 5}); displayTable(table);
	addPair(table, (t_pair){18, 12}); displayTable(table);
	addPair(table, (t_pair){18, 15}); displayTable(table);
}