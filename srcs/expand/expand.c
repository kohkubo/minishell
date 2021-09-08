#include "shell.h"

static char	*wrapper_hash_getstr(t_hash_table *h, char *key)
{
	char	*tmp;

	tmp = (char *)hash_getstr(h, key);
	if (tmp == NULL)
		return ("");
	return (tmp);
}

static char	*minishell_expand2(char *arg, char *ret, char *ptr)
{
	char	*tmp;

	while (1)
	{
		if (arg[1] == '\0')
		{
			free_set((void **)&ret, ft_xstrjoin(ret, "$"));
			break ;
		}
		ptr = ft_strchr(arg + 1, '$');
		if (ptr == NULL)
		{
			tmp = wrapper_hash_getstr(g_shell.env, &arg[1]);
			free_set((void **)&ret, ft_xstrjoin(ret, tmp));
			break ;
		}
		*ptr = '\0';
		tmp = wrapper_hash_getstr(g_shell.env, &arg[1]);
		free_set((void **)&ret, ft_xstrjoin(ret, tmp));
		arg += ptr - arg;
	}
	return (ret);
}

char	*minishell_expand(char *arg)
{
	char	*ret;
	char	*ptr;

	ptr = NULL;
	if (arg == NULL)
		ft_fatal("minishell_expand : Invalid argument");
	if (ft_strchr(arg, '$') == NULL)
		return (ft_xstrdup(arg));
	if (arg[0] == '$' && arg[1] == '\0')
		return (ft_xstrdup("$"));
	ret = NULL;
	if (arg[0] == '$')
		ret = ft_xstrdup("");
	else
	{
		ptr = ft_strchr(arg, '$');
		*ptr = '\0';
		ret = ft_xstrdup(arg);
		arg += ptr - arg;
		*ptr = '$';
	}
	return (minishell_expand2(arg, ret, ptr));
}
