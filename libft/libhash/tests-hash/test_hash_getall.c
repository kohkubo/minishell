#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

void	test_hash_getall(char **ans, t_hash_table *table, int *ret)
{
	int		i;
	int		j;
	char	*key1;
	char	*key2;
	char	*value;

	i = 0;
	j = 0;
	while (i < 10)
	{
		key1 = random_string(rand() % 100);
		key2 = random_string(rand() % 100);
		value = random_string(rand() % 100);
		ans[j++] = strdup(key1), hash_setstr(table, key1, value);
		ans[j++] = strdup(key2), hash_setint(table, key2, i);
		if (hash_getint(table, key2, ret) != true && *ret != i)
			exit(1);
		if (strcmp(hash_getstr(table, key1), value))
			exit(1);
		free(key1);
		free(key2);
		free(value);
		i++;
	}
	ans[j] = NULL;
}

int	main(void)
{
	t_hash_table	*table;
	int				ret;
	bool			success;
	char			**ans;

	srand((unsigned)time(NULL));
	table = hash_create_table(10);
	ans = calloc(sizeof(char *), 21);
	test_hash_getall(ans, table, &ret);
	hash_setstr(table, "ENV", "test");
	success = hash_getint(table, "ENV", &ret);
	if (success != true && ret != 0)
		exit(1);
	success = hash_getint(table, "aaaaaaaaaaaaaaaaaaaaaaaa", &ret);
	if (success != false)
		exit(1);
	hash_clear_table(&table);
	free_string_array(ans);
	return (0);
}
