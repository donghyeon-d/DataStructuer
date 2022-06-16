#ifndef _HASH_H_
#define _HASH_H_

#define TRUE 1
#define FALSE 0

#define NOT_USED 0
#define USE 1
#define USED 2

typedef struct s_pair
{
    int key;
	int value;
} t_pair;

typedef struct s_hashTable
{
    int     maxCount;
    int     currentCount;
    int     *used;
    t_pair  *hashTable;
}   t_hashTable;

t_hashTable *createHashTable(int maxCount);
void	deleteHashTable(t_hashTable *table);
int		addPair(t_hashTable *table, t_pair pair);
t_pair	*deletePair(t_hashTable *table, t_pair pair); // pop
t_pair	*searchPair(t_hashTable *table, t_pair key); // peek
int     pairCount(t_hashTable *table);
int		isHashTableFull(t_hashTable *table);
int		isHashTableEmpty(t_hashTable *table);
int     isUsedIndex(t_hashTable *table, int index);
int     ft_hashing(int maxCount, int key);//mod

#endif