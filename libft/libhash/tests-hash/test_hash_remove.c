#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

int	catch_error(int state);

// 存在しないものを消去
// リストの途中のものを消去
void	test_hash_remove1(void)
{
	t_hash_table	*table;

	table = hash_create_table(10);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	catch_error(hash_remove(table, "aiueo0") != true || table->count != 3);
	catch_error(hash_remove(table, "aiueo1") != true || table->count != 2);
	catch_error(hash_remove(table, "aiueo2") != true || table->count != 1);
	catch_error(hash_remove(table, "aiueo3") != true || table->count != 0);
	catch_error(hash_remove(table, "aiueo3") != false || table->count != 0);
	catch_error(hash_remove(table, "aiueo3") != false || table->count != 0);
	catch_error(hash_remove(table, "aiueo3") != false || table->count != 0);
	catch_error(hash_remove(table, "aiueo3") != false || table->count != 0);
	catch_error(hash_remove(table, "aiueo3") != false || table->count != 0);
	catch_error(hash_remove(table, "aaaaaa") != false || table->count != 0);
	hash_clear_table(&table);
}

// リストの最初の要素を消去
void	test_hash_remove2(void)
{
	t_hash_table	*table;
	char			**all;
	char			**ex;

	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_setstr(table, "aiueo4", "15");
	catch_error(hash_remove(table, "aiueo2") != true || table->count != 4);
	catch_error(hash_contains_key(table, "aiueo2"));
	all = hash_getall(table, NULL);
	ex = ft_split("aiueo4=15 aiueo3=16 aiueo1=18 aiueo0=19", ' ');
	if (debug_arraycmp(all, ex) != -1 || !hash_clear_table(&table))
	{
		all = free_string_array(all);
		ex = free_string_array(ex);
		exit(1);
	}
	all = free_string_array(all);
	ex = free_string_array(ex);
}

// リストの最後の要素を消去
void	test_hash_remove3(void)
{
	t_hash_table	*table;
	char			**all;
	char			**ex;

	table = hash_create_table(1);
	hash_setstr(table, "aiueo0", "19");
	hash_setstr(table, "aiueo1", "18");
	hash_setstr(table, "aiueo2", "17");
	hash_setstr(table, "aiueo3", "16");
	hash_setstr(table, "aiueo4", "15");
	catch_error(hash_remove(table, "aiueo3") != true
		|| table->count != 4 || hash_contains_key(table, "aiueo3"));
	all = hash_getall(table, NULL);
	ex = ft_split("aiueo4=15 aiueo2=17 aiueo1=18 aiueo0=19", ' ');
	if (debug_arraycmp(all, ex) != -1 || !hash_clear_table(&table))
	{
		all = free_string_array(all);
		ex = free_string_array(ex);
		exit (1);
	}
	all = free_string_array(all);
	ex = free_string_array(ex);
}

// randomテスト
void	test_hash_remove4(int i)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	int				count;

	table = hash_create_table(1);
	count = 0;
	i = 0;
	while (i < 100)
	{
		key = random_string(rand() % 100);
		value = random_string(rand() % 100);
		if (hash_setstr(table, key, value))
			count++;
		free(key), free(value), i++;
	}
	i = 0;
	while (i < 100)
	{
		key = random_string(rand() % 100);
		if (hash_remove(table, key))
			count--;
		free(key), i++;
	}
	catch_error(table->count != count), hash_clear_table(&table);
}

int	main(void)
{
	t_hash_table	*table;

	srand((unsigned) time(NULL));
	test_hash_remove1();
	test_hash_remove2();
	test_hash_remove3();
	test_hash_remove4(0);
	return (0);
}
