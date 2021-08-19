#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

#define TABLE_SIZE 10000

int	main()
{
	srand((unsigned) time(NULL));
	t_hash_table	*table;
	t_dict_item			*item;

	table = hash_create_table(TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		char *key = malloc(100);
		char *value = malloc(100);
		sprintf(key, "test%d", i);
		sprintf(value, "aiueo%d", i);
		hash_setstr(table, key, value);
		free(key);
		free(value);
	}
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		char *key = malloc(100);
		char *value = malloc(100);
		sprintf(key, "test%d", i);
		sprintf(value, "aiueo%d", i);

		item = hash_search(table, key);
		if (strcmp(value, item->value))
			exit(1);
		free(key);
		free(value);
	}

	if (!hash_setstr(table, "CD", "aa"))
		exit (1);
	if (!hash_setstr(table, "ENB", "bb"))
		exit (1);
	if (!hash_setstr(table, "ASA", "c"))
		exit (1);
	if (!hash_setstr(table, "aあ", "いいいい"))
		exit (1);
	// 同じkeyでinsertして更新されるかテスト
	if (!hash_setstr(table, "ええ", "b"))
		exit (1);
	if (hash_setstr(table, "ええ", "c"))
		exit (1);
	if (!hash_setstr(table, "", "d"))
		exit (1);
	if (hash_setstr(table, "", ""))
		exit (1);
	if (hash_setstr(table, "", ""))
		exit (1);
	if (hash_setstr(table, "", "dd"))
		exit (1);

	if (strcmp(hash_getstr(table, "ええ"), "c"))
		exit(1);
	item = hash_search(table, "");
	if (strcmp("dd", item->value))
		exit(1);
	if (table->count != TABLE_SIZE + 6)
		exit(1);

	// printf("\ntable 消去のチェック\n");
	hash_clear_table(&table);

	// printf("\nランダム文字列を挿入\n");
	int count = 0;
	table = hash_create_table(TABLE_SIZE);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		char *key = random_string(rand() % 100);
		char *value = random_string(rand() % 100);
		if (hash_setstr(table, key, value))
			count++;
		if (strcmp(value, hash_getstr(table, key)))
			exit(1);
		free(key);
		free(value);
	}
	printf("table->count : %d\n", table->count);
	if (table->count != count)
		exit(1);
	hash_clear_table(&table);
	return 0;
}
