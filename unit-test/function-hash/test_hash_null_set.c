#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include "libdebug.h"
#include <libc.h>

static void	test_res_null(t_hash_table *t, char *key)
{
	t_dict_item *item = hash_search(t, key);

	if (!item && item->value != NULL)
		exit(1);
}

int	main()
{
	t_hash_table *t;

	t = hash_create_table(10);

	// setのチェック、上書きのチェック
	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL2", NULL);
	hash_setstr(t, "VAL3", "test");
	hash_setstr(t, "VAL0", NULL);
	hash_setstr(t, "VAL5", NULL);
	hash_setstr(t, "VAL6", NULL);

	// getstrできるか
	char *val0 = hash_getstr(t, "VAL7");
	if (val0 != NULL)
		exit(1);
	// NULLが格納されているかのチェック
	test_res_null(t, "VAL0");
	test_res_null(t, "VAL2");
	test_res_null(t, "VAL5");
	test_res_null(t, "VAL6");

	// getallのチェック
	char **arr = hash_getall(t);
	qsort_strarray(arr);
	char **ans = ft_split("VAL0 VAL2 VAL3=test VAL5 VAL6", ' ');
	if (array_cmp(arr, ans) != -1)
		exit(1);
	free_string_array(arr);
	free_string_array(ans);

	// 消去のチェック
	hash_remove(t, "VAL2");
	t_dict_item *item = hash_search(t, "VAL2");
	if (item != NULL)
		exit(1);

	// NULLで上書きされているか
	hash_setstr(t, "VAL3", NULL);
	test_res_null(t, "VAL3");

	//もともとNULLのときに上書きできるかチェック
	test_res_null(t, "VAL5");
	hash_setstr(t, "VAL5", "aiueo");
	char *val5 = hash_getstr(t, "VAL5");
	if (strcmp(val5, "aiueo"))
		exit(1);

	hash_clear_table(&t);

	return 0;
}
