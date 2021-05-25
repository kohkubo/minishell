#include "./../../../libft/libft/libft.h"
#include "./../../../libft/libex/libex.h"
#include "./../../../libft/libhash/libhash.h"
#include "./../../../libft/libdebug/libdebug.h"

#include <libc.h>

int main()
{
	t_hash_table	*table;
	srand((unsigned) time(NULL));
	bool success;

	table = hash_create_table(10);

	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	success = hash_remove(table, "aiueo0");
	if (success != true || table->count != 3)
		exit(1);
	success = hash_remove(table, "aiueo1");
	if (success != true || table->count != 2)
		exit(1);
	success = hash_remove(table, "aiueo2");
	if (success != true || table->count != 1)
		exit(1);
	success = hash_remove(table, "aiueo3");
	if (success != true || table->count != 0)
		exit(1);

	// 存在しないものを消去
	success = hash_remove(table, "aiueo3");
	if (success != false || table->count != 0)
		exit(1);
	success = hash_remove(table, "aiueo3");
	if (success != false || table->count != 0)
		exit(1);
	success = hash_remove(table, "aiueo3");
	if (success != false || table->count != 0)
		exit(1);
	success = hash_remove(table, "aiueo3");
	if (success != false || table->count != 0)
		exit(1);
	success = hash_remove(table, "aiueo3");
	if (success != false || table->count != 0)
		exit(1);
	success = hash_remove(table, "aaaaaa");
	if (success != false || table->count != 0)
		exit(1);
	hash_clear_table(&table);

	// printf("リストの途中のものを消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	success = hash_remove(table, "aiueo2");
	hash_setstr(table, "aiueo4", "15");
	if (success != true || table->count != 4)
		exit(1);
	if (hash_contains_key(table, "aiueo2"));
		exit(1);
	char **all = hash_getall(table);
	char ex1[][15] = {
		"aiueo0=19", "aiueo1=18", "aiueo3=16", "aiueo4=15",NULL,
	};
	if (array_cmp(all, ex1) != -1 || !hash_clear_table(&table))
		exit (1);
	all = free_string_array(all);


	// printf("リストの最初の要素を消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	success = hash_remove(table, "aiueo0");
	hash_setstr(table, "aiueo4", "15");
	if (success != true || table->count != 4 || hash_contains_key(table, "aiueo0"))
		exit(1);
	all = hash_getall(table);
	char ex2[][15] = {
		"aiueo1=18", "aiueo2=17", "aiueo3=16", "aiueo4=15",NULL,
	};
	if (array_cmp(all, ex2) != -1 || !hash_clear_table(&table))
		exit(1);
	all = free_string_array(all);

	// printf("リストの最後の要素を消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	success = hash_remove(table, "aiueo3");
	hash_setstr(table, "aiueo4", "15");
	if (success != true || table->count != 4 || hash_contains_key(table, "aiueo3"))
		exit(1);
	all = hash_getall(table);
	char ex3[][15] = {
		"aiueo0=19", "aiueo1=18","aiueo2=17", "aiueo4=15", NULL,
	};
	if (array_cmp(all, ex3) != -1 || !hash_clear_table(&table))
		exit(1);
	all = free_string_array(all);

	// printf("ランダムテスト\n");
	table = hash_create_table(1);
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		char *key = debug_rand_text(rand() % 100);
		char *value = debug_rand_text(rand() % 100);
		if (hash_setstr(table, key, value))
			count++;
		free(key);
		free(value);
	}
	int delcount = 0;
	for (int i = 0; i < 100; i++)
	{
		char *key = debug_rand_text(rand() % 100);
		if (hash_remove(table, key))
			delcount++;
		free(key);
	}
	printf("delcount : %d\n", delcount);
	printf("   count : %d\n", count);
	if (table->count != count - delcount)
		exit(1);
	hash_clear_table(&table);
	return (0);
}
