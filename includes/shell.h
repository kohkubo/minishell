/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywake <ywake@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:15 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/27 18:37:39 by ywake            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "libex.h"
# include "libhash.h"
# define PROMPT "minishell> "
# define QUOTE_PROMPT "quote... "
# define DQUOTE_PROMPT "dquote... "
# define HEREDOC_PROMPT "heredoc... "
# include "lex.h"
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	t_hash_table	*env;
}	t_shell;

extern t_shell	g_shell;

t_state_type	minishell_lexer(char *s, t_lexer **lexer);
void			parse(char *input);
int				ft_exit(char **arg);
int				ft_echo(char **args);
void			minishell_init(void);
void			store_shellenv(char **arr, t_hash_table *table);
int				ft_env(char **args);

#endif
