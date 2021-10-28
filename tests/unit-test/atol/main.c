#include <libc.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdbool.h>

long ft_atol(const char *str);

void check_atoi(const char *str)
{
	long ft;
	long libc;

	errno = 0;
	ft = ft_atol(str);
	libc = atol(str);
	if (ft != libc)
	{
		printf("\033[31m");
		printf("errno : %d\n", errno);
		printf("%s\n", str);
		printf("ft_atol: %ld\n", ft);
		printf("atol: %ld\n", libc);
		printf("%s\n", "error");
		printf("\033[0m");
	}
	else
	{
		// printf("errno : %d\n", errno);
		printf("%s\n", str);
		// printf("ft_atol: %ld\n", ft);
		// printf("atol: %ld\n", libc);
		printf("OK\n");
	}
}

int main() {

	// intMaxMin
	check_atoi(" 2147483645");
	check_atoi(" 2147483646");
	check_atoi(" 2147483647");
	check_atoi(" 2147483648");
	check_atoi(" 2147483649");
	check_atoi("-2147483645");
	check_atoi("-2147483646");
	check_atoi("-2147483647");
	check_atoi("-2147483648");
	check_atoi("-2147483649");
	check_atoi("-0002147483649");
	check_atoi("-000");

	// longMaxMin
	check_atoi("63410682753376583680");
	check_atoi("63410682753376583681");
	check_atoi("-63410682753376583680");
	check_atoi("-63410682753376583681");
	check_atoi("9223372036850000000");
	check_atoi("9223372036854775000");
	check_atoi("9223372036854775805");
	check_atoi("9223372036854775806");
	check_atoi("9223372036854775807");
	check_atoi("9223372036854775808");
	check_atoi("9223372036854775809");
	check_atoi("-9223372036854775805");
	check_atoi("-9223372036854775806");
	check_atoi("-9223372036854775807");
	check_atoi("-9223372036854775808");
	check_atoi("-9223372036854775809");
	check_atoi("18446744073700000000");
	check_atoi("18446744073709551613");
	check_atoi("18446744073709551614");
	check_atoi("18446744073709551615");
	check_atoi("18446744073709551616");
	check_atoi("18446744073709551617");
	check_atoi("-18446744073709551613");
	check_atoi("-18446744073709551614");
	check_atoi("-18446744073709551615");
	check_atoi("-18446744073709551616");
	check_atoi("-18446744073709551617");
	check_atoi("63410682753376583678");
	check_atoi("63410682753376583679");
	check_atoi("63410682753376583680");
	check_atoi("63410682753376583681");
	check_atoi("63410682753376583682");
	check_atoi("-63410682753376583678");
	check_atoi("-63410682753376583679");
	check_atoi("-63410682753376583680");
	check_atoi("-63410682753376583681");
	check_atoi("-63410682753376583682");

	check_atoi("a");
	check_atoi("\0");
	check_atoi("100\n");
	check_atoi("-1100");
	check_atoi("-");
	check_atoi("  12345  6789");
	check_atoi("  ");
	check_atoi("3456  ");
	check_atoi("\01012346  6789");
	check_atoi("\01112347  6789");
	check_atoi("\01212348  6789");
	check_atoi("\01312349  6789");
	check_atoi("\01412350  6789");
	check_atoi("\01512351  6789");
	check_atoi("\01612352  6789");
	check_atoi("\01712353  6789");
	check_atoi("\010\0102346  6789");
	check_atoi("\011\0112347  6789");
	check_atoi("\012\0122348  6789");
	check_atoi("\013\0132349  6789");
	check_atoi("\014\0142350  6789");
	check_atoi("\015\0152351  6789");
	check_atoi("\016\0162352  6789");
	check_atoi("\017\0172353  6789");
	check_atoi("\t\v\f\r\n \f- \f\t\n\r    06050");
	check_atoi("\t\v\f\r\n \f-06050");
	check_atoi("-123THERE IS A NYANCAT UNDER YOUR BED");
	check_atoi("123456789");
	check_atoi("12345  6789");
	check_atoi("1234\056789");
	check_atoi("2147483648");
	check_atoi("+2147483647");
	check_atoi("2147483647");
	check_atoi("-2147483648");
	check_atoi("-2147483649");
	check_atoi("6442450944");
	check_atoi("4294969344");
	check_atoi("-9223372036854775808");
	check_atoi("-92233720368547758081");
	check_atoi("-9223372036854775808a");
	check_atoi("-9223372036854775807a");
	check_atoi("-922337203685477580a");
	check_atoi("9223372036854775807");
	check_atoi("92233720368547758071");
	check_atoi("9223372036854775807a");
	check_atoi("9223372036854775806a");
	check_atoi("922337203685477580a");
	check_atoi("-9223372036854775809");
	check_atoi("9223372036854775808");
	check_atoi("63410682753376583680");

	return (0);
}
