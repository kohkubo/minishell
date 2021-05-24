#include "./../../../libft/libex/libex.h"
#include <libc.h>

#define PP(str) printf("%d : %s\n", __LINE__, #str); str;

char *rand_text()
{
	char char_set[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char *text = calloc(100, 1);

	for (int i = 0; i < 6; i++)
	{
		text[i] = char_set[rand() % (sizeof(char_set))];
	}
	return (text);
}
int main()
{
	t_hash_table	*table;
	srand((unsigned) time(NULL));

	table = hash_create_table(10);

	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_remove(table, "aiueo0");
	hash_remove(table, "aiueo1");
	hash_remove(table, "aiueo2");
	hash_remove(table, "aiueo3");
	if (table->count != 0)
		exit(1);

	// 存在しないものを消去
	hash_remove(table, "aiueo3");
	hash_remove(table, "aiueo3");
	hash_remove(table, "aiueo3");
	hash_remove(table, "aiueo3");
	hash_remove(table, "aiueo3");
	hash_remove(table, "aaaaaa");
	if (table->count != 0)
		exit(1);
	hash_clear_table(&table);

	// printf("リストの途中のものを消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_remove(table, "aiueo2");
	hash_setstr(table, "aiueo4", "15");
	if (table->count != 4)
		exit(1);
	hash_clear_table(&table);

	// printf("リストの最初の要素を消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_remove(table, "aiueo0");
	hash_setstr(table, "aiueo4", "15");
	if (table->count != 4 && !hash_contains_key(table, "aiueo0"))
		exit(1);
	hash_clear_table(&table);

	// printf("リストの最後の要素を消去\n");
	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_remove(table, "aiueo3");
	hash_setstr(table, "aiueo4", "15");
	if (table->count != 4 && !hash_contains_key(table, "aiueo3"))
		exit(1);
	hash_clear_table(&table);

	// printf("ランダムテスト\n");
	table = hash_create_table(1);
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		char *key = rand_text();
		char *value = rand_text();
		if (hash_setstr(table, key, value))
			count++;
	}
	int delcount = 0;
	for (int i = 0; i < 100; i++)
	{
		char *key = rand_text();
		if (hash_remove(table, key))
			delcount++;
	}
	printf("delcount : %d\n", delcount);
	printf("   count : %d\n", count);
	if (table->count != count - delcount)
		exit(1);
	return (0);
}
