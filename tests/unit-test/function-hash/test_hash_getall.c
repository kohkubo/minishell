#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

int main()
{
	t_hash_table *table;
	srand((unsigned)time(NULL));
	int ret;
	bool success;

	table = hash_create_table(10);
	char **ans = calloc(sizeof(char *), 21);
	int j = 0;
	for (int i = 0; i < 10; i++)
	{
		char *key1 = random_string(rand() % 100);
		char *key2 = random_string(rand() % 100);
		char *value = random_string(rand() % 100);
		ans[j++] = strdup(key1);
		hash_setstr(table, key1, value);
		ans[j++] = strdup(key2);
		hash_setint(table, key2, i);
		success = hash_getint(table, key2, &ret);
		if (success != true && ret != i)
			exit(1);
		if (strcmp(hash_getstr(table, key1), value))
			exit(1);
		free(key1);
		free(key2);
		free(value);
	}
	ans[j] = NULL;
	hash_setstr(table, "ENV", "test");
	success = hash_getint(table, "ENV", &ret);
	if (success != true && ret != 0)
		exit(1);
	success = hash_getint(table, "aaaaaaaaaaaaaaaaaaaaaaaa", &ret);
	if (success != false)
		exit(1);

	hash_clear_table(&table);

	// ソートのチェック
	// char **aa = hash_getall(table, NULL);
	// char **bb = str_arraydup(aa);
	// qsort(bb, arraylen(bb), sizeof(char *), compare);
	// qsort(ans, arraylen(ans), sizeof(char *), compare);
	// char **cc = hash_getkeys(table);
	// if (debug_arraycmp(cc, ans) != -1)
	// 	exit(1);

	free_string_array(ans);
	return 0;
}
