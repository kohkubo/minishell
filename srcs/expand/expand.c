#include "shell.h"

char *minishell_expand(char *arg)
{
	char	*tmp;
	char	*ret;
	char	*ptr;

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
			tmp = (char *)hash_getstr(g_shell.env, &arg[1]);
			if (tmp == NULL)
				tmp = "";
			free_set((void **)&ret, ft_xstrjoin(ret, tmp));
			break ;
		}
		*ptr = '\0';
		tmp = (char *)hash_getstr(g_shell.env, &arg[1]);
		if (tmp == NULL)
			tmp = "";
		free_set((void **)&ret, ft_xstrjoin(ret, tmp));
		arg += ptr - arg;
	}
	return (ret);
}
