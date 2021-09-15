#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

#define TABLE_SIZE 10000

int	catch_error(int state);

void	test_hash_setstr(t_hash_table *table)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (i < TABLE_SIZE)
	{
		key = malloc(100);
		value = malloc(100);
		sprintf(key, "test%d", i);
		sprintf(value, "aiueo%d", i);
		hash_setstr(table, key, value);
		free(key);
		free(value);
		i++;
	}
}

void	test_hash_setstr2(t_hash_table *table)
{
	int				i;
	char			*key;
	char			*value;
	t_dict_item		*item;

	i = 0;
	while (i < TABLE_SIZE)
	{
		key = malloc(100);
		value = malloc(100);
		sprintf(key, "test%d", i);
		sprintf(value, "aiueo%d", i);
		item = hash_search(table, key);
		catch_error(strcmp(value, item->value));
		free(key);
		free(value);
		i++;
	}
}

void	test_hash_setstr3(void)
{
	t_hash_table	*table;
	int				i;
	int				count;
	char			*key;
	char			*value;

	table = hash_create_table(TABLE_SIZE);
	count = 0;
	i = 0;
	while (i < TABLE_SIZE)
	{
		key = random_string(rand() % 100);
		value = random_string(rand() % 100);
		if (hash_setstr(table, key, value))
			count++;
		catch_error(strcmp(value, hash_getstr(table, key)));
		free(key);
		free(value);
		i++;
	}
	catch_error(table->count != count);
	hash_clear_table(&table);
}

int	main(void)
{
	t_hash_table	*table;
	t_dict_item		*item;

	srand((unsigned) time(NULL));
	table = hash_create_table(TABLE_SIZE);
	test_hash_setstr(table);
	test_hash_setstr2(table);
	catch_error(!hash_setstr(table, "CD", "aa"));
	catch_error(!hash_setstr(table, "ENB", "bb"));
	catch_error(!hash_setstr(table, "ASA", "c"));
	catch_error(!hash_setstr(table, "aあ", "いいいい"));
	catch_error(!hash_setstr(table, "ええ", "b"));
	catch_error(hash_setstr(table, "ええ", "c"));
	catch_error(!hash_setstr(table, "", "d"));
	catch_error(hash_setstr(table, "", ""));
	catch_error(hash_setstr(table, "", ""));
	catch_error(hash_setstr(table, "", "dd"));
	catch_error(strcmp(hash_getstr(table, "ええ"), "c"));
	item = hash_search(table, "");
	catch_error(strcmp("dd", item->value));
	catch_error(table->count != TABLE_SIZE + 6);
	hash_clear_table(&table);
	test_hash_setstr3();
	return (0);
}
