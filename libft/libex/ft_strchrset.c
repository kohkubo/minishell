#include "libex.h"

char	*ft_strchrset(const char *s, char *chrset, size_t chrset_len)
{
	size_t	i;
	char	*find;

	while (*s)
	{
		i = 0;
		while (i < chrset_len)
		{
			find = ft_strchr(s++, chrset[i]);
			if (find)
				return (find);
			i++;
		}
	}
	return (NULL);
}

#ifdef FT_STRCHRSET_DEBUG

bool	test(char *str, char *chrset, size_t chrset_len, size_t expect_char_at)
{
	char	*tmp;

	tmp = ft_strchrset(str, chrset, chrset_len);
	if (expect_char_at == tmp - str)
		return (true);
	return (false);
}

int	main(void)
{
	bool	flg;

	flg = true;
	flg &= test("test", "t", 1, 0);
	flg &= test("test", "e", 1, 1);
	flg &= test("test", "s", 1, 2);
	flg &= test("test", "\0", 1, 4);
	flg &= test("test", "as", 2, 2);
	flg &= test("test", "a\0b", 3, 4);
	if (flg)
		write(2, "OK!\n", 4);
	else
		write(2, "KO...\n", 6);
	return (!flg);
}
#endif
