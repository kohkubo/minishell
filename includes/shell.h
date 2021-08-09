/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:06:15 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:06:15 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "../libft/libft/libft.h"
# include "../libft/libex/libex.h"
# include "../libft/libhash/libhash.h"
# ifdef DEBUG
#  include "../libft/libdebug/libdebug.h"
# endif
# include "lex.h"
# include <stdio.h>
# include <stdbool.h>

t_lexer			*minishell_lexer(char *s);
void			parse(char *input);
int				ft_exit(char **arg);
int				ft_echo(char **args);

#endif
