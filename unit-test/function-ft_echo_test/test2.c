#include <stdio.h>
#include <libc.h>
#include "./../../../includes/shell.h"

int main()
{
	char *ss[100];
	int i = 0;

	char *ss00[100] = {"1", "2", NULL};
	char *ss01[100] = {"-n", "-n\n", NULL};
	char *ss02[100] = {"-n", "-n", "aiueo\n", NULL};
	char *ss03[100] = {"-n", "-n", "test", "-n\n", NULL};
	char *ss04[100] = {"-na", "-n", "test", "-n", NULL};
	char *ss05[100] = {"a-n", "-n", "test", "-n", NULL};
	char *ss06[100] = {"-", "n", "test", "-n", NULL};
	char *ss07[100] = {"-", "aaa  aaaaaaaaaaaaaa  ", "*", "\\", NULL};
	char *ss08[100] = {"    ", NULL};
	char *ss09[100] = {" ", NULL};
	char *ss10[100] = {"", NULL};
	char *ss11[100] = {"-n", "", NULL};
	char *ss12[100] = {"-n", " ", NULL};
	char *ss13[100] = {"  d", NULL};
	// echo "" "" "" "" > echo_test 区切りスペースのみが出力される
	char *ss14[100] = {"", "", "", "", NULL};
	char *ss15[100] = {NULL, NULL};

	ft_echo(ss00);
	ft_echo(ss01);
	ft_echo(ss02);
	ft_echo(ss03);
	ft_echo(ss04);
	ft_echo(ss05);
	ft_echo(ss06);
	ft_echo(ss07);
	ft_echo(ss08);
	ft_echo(ss09);
	ft_echo(ss10);
	ft_echo(ss11);
	ft_echo(ss12);
	ft_echo(ss13);
	ft_echo(ss14);
	ft_echo(ss15);

	return (0);
}
