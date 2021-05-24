#include "./../../../libft/libex/libex.h"
#include <libc.h>

#define PP(str)                          \
	printf("%d : %s\n", __LINE__, #str); \
	str;

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

char **str_array_dup(char **array, int n)
{
	int i;
	char **ss;
	char **head;

	ss = calloc(sizeof(char *), n + 1);
	head = ss;
	i = 0;
	while (i < n)
	{
		ss[i] = ft_strdup(array[i]);
		i++;
	}
	ss[i] = 0;
	return (head);
}

void array_cmp(char **aa, char **bb)
{
	int i = 0;

	while (aa[i] && bb[i])
	{
		if (ft_strcmp(aa[i], bb[i]))
		{
			printf("%s : %s\n", aa[i], bb[i]);
			exit(1);
		}
		i++;
	}
}

int compare(const void *stackA, const void *stackB)
{
	const char *a = *(const char **)stackA;
	const char *b = *(const char **)stackB;
	return strcmp(a, b);
}

void	display_array(char **array)
{
	while (*array)
		printf("%s\n", *array++);
}

int	arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int main()
{
	t_hash_table *table;
	srand((unsigned)time(NULL));

	table = hash_create_table(10);
	char **ans = calloc(sizeof(char *), 10000);
	int j = 0;
	for (int i = 0; i < 10; i++)
	{
		char *key1 = rand_text();
		char *key2 = rand_text();
		char *value = rand_text();
		ans[j++] = strdup(key1);
		hash_setstr(table, key1, value);
		ans[j++] = strdup(key2);
		hash_setint(table, key2, i);
		if (hash_getint(table, key2) != i)
			exit(1);
		if (strcmp(hash_getstr(table, key1), value))
			exit(1);
	}
	ans[j] = NULL;
	if (hash_getint(table, "ENV"))
		exit(1);
	if (hash_getint(table, "aaaaaaaaaaaaaaaaaaaaaaaa"))
		exit(1);

	// ソートのチェック
	char **aa = hash_getall(table);
	char **bb = str_array_dup(aa, table->count);
	qsort(bb, arraylen(bb), sizeof(char *), compare);
	qsort(ans, arraylen(ans), sizeof(char *), compare);
	char **cc = hash_getkeys(table);
	array_cmp(cc, ans);

	return 0;
}
