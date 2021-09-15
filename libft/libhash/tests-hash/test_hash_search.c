#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

int	catch_error(int state);

int	main(void)
{
	t_hash_table	*table;
	t_dict_item		*item;

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
	item = hash_search(table, "ENV");
	catch_error(!item && strcmp(item->value, "aaaaaaaa"));
	item = hash_search(table, "");
	catch_error(!item && strcmp(item->value, "kara"));
	hash_remove(table, "");
	catch_error(hash_contains_key(table, ""));
	catch_error(hash_search(table, "") != NULL);
	hash_clear_table(&table);
	return (0);
}
