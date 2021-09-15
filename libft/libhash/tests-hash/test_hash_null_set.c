#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

static int	compare(const void *a, const void *b)
{
	return (ft_strcmp(*(const char **)a, *(const char **)b));
}

static void	qsort_strarray(char **array)
{
	qsort(array, arraylen(array), sizeof(char *), compare);
}

static void	test_res_null(t_hash_table *t, char *key)
{
	t_dict_item	*item;

	item = hash_search(t, key);
	if (!item && item->value != NULL)
		exit(1);
}

// setのチェック、上書きのチェック
// getstrできるか
// NULLが格納されているかのチェック
// getallのチェック
void	test_hash_null_set(t_hash_table *t)
{
	char	**arr;
	char	**ans;

	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL2", NULL);
	hash_setstr(t, "VAL3", "test");
	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL5", NULL);
	hash_setstr(t, "VAL6", NULL);
	if (hash_getstr(t, "VAL7") != NULL)
		exit(1);
	test_res_null(t, "VAL0");
	test_res_null(t, "VAL2");
	test_res_null(t, "VAL5");
	test_res_null(t, "VAL6");
	arr = hash_getall(t, NULL);
	qsort_strarray(arr);
	ans = ft_split("VAL0 VAL2 VAL3=test VAL5 VAL6", ' ');
	if (debug_arraycmp(arr, ans) != -1)
		exit(1);
	free_string_array(arr);
	free_string_array(ans);
}

int	main(void)
{
	t_hash_table	*t;

	t = hash_create_table(10);
	test_hash_null_set(t);
	hash_remove(t, "VAL2");
	if (hash_search(t, "VAL2") != NULL)
		exit(1);
	hash_setstr(t, "VAL3", NULL);
	test_res_null(t, "VAL3");
	test_res_null(t, "VAL5");
	hash_setstr(t, "VAL5", "aiueo");
	if (strcmp(hash_getstr(t, "VAL5"), "aiueo"))
		exit(1);
	hash_clear_table(&t);
	return (0);
}
