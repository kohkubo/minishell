#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

int	main()
{
	t_hash_table *table;

	table = hash_create_table(100);
	hash_setstr(table, "ENV", "aaaaaaaa");
	hash_setstr(table, "ENVa", "bbbbb");
	hash_setstr(table, "ENVb", "c");
	hash_setstr(table, "ENVc", "");
	hash_setstr(table, "ENVd", "aaaaaaaa");
	hash_setstr(table, " ENV", "a");
	hash_setstr(table, "", "kara");
	hash_setstr(table, " ", "space");
	hash_setstr(table, "  ", "space2");

	t_dict_item *item = hash_search(table, "ENV");
	if (!item && strcmp(item->value, "aaaaaaaa"))
		exit(1);

	item = hash_search(table, "");
	if (!item && strcmp(item->value, "kara"))
		exit(1);
	hash_remove(table, "");

	if (hash_contains_key(table, ""))
		exit(1);

	if (hash_search(table, ""))
		exit(1);

	// エラーケース
	// hash_search(table, NULL);
	hash_clear_table(&table);

	return 0;
}
