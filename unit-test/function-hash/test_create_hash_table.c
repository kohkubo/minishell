#include "libft.h"
#include "libex.h"
#include "libhash.h"
#include <libc.h>

# define PP(str) printf("    %d : %s\n", __LINE__, #str); str;

static void	test_table_null(int size)
{
	t_hash_table *table = hash_create_table(size);
	if (table != NULL)
		exit(1);
}

int	main()
{
	t_hash_table *table;

	test_table_null(0);
	test_table_null(-1);
	test_table_null(-2147483648);

	// 時間がかかるためコメントアウト
	// table = hash_create_table(2147483647);
	table = hash_create_table(1);
	if (table->tsize != 1)
		exit(1);
	hash_clear_table(&table);
	table = hash_create_table(214);
	if (table->tsize != 214)
		exit(1);
	hash_clear_table(&table);
	table = hash_create_table(2147);
	if (table->tsize != 2147)
		exit(1);
	hash_clear_table(&table);

	// ランダムテスト
	srand((unsigned) time(NULL));
	int i = rand() % 10000 + 1;
	printf("rand(): %d\n", i);
	table = hash_create_table(i);
	hash_clear_table(&table);

	return 0;
}
