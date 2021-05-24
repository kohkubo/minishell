#include "./../../../libft/libex/libex.h"

#include <libc.h>

#define PP(str) printf("    %d : %s\n", __LINE__, #str); str;

static void	test_table_null(int size)
{
	t_hash_table *table = hash_create_table(size);
	if (table != NULL)
		exit(1);
}

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

int	main()
{
	t_hash_table *table;
	// エラーケース
	test_table_null(0);

	test_table_null(-1);
	test_table_null(-2147483648);

	// 時間がかかるためコメントアウト
	// PP(table = hash_create_table(2147483647);)
	table = hash_create_table(1);
	if (table->tsize != 1)
		exit(1);
	table = hash_create_table(214);
	if (table->tsize != 214)
		exit(1);
	table = hash_create_table(2147);
	if (table->tsize != 2147)
		exit(1);

	// ランダムテスト
	srand((unsigned) time(NULL));
	int i = rand() % 10000 + 1;
	printf("rand(): %d\n", i);
	table = hash_create_table(i);
	table = hash_create_table(10);
	hash_setstr(table, "test", "aiueo");
	// hash_display_table(table);
	return 0;
}
