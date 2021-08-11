/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:50 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/09 16:01:51 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBEX_H
# define LIBEX_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

void	strsort(char *str[], int n);
char	**free_string_array(char **buf);
int		get_next_line(int fd, char **line);
int		min(int a, int b);
void	free_set(void **dst, void *src);
void	*ft_xmalloc(size_t size);
void	ft_fatal(const char *emsg);
void	ft_error_exit(const char *emsg);
char	*ft_strndup(const char *s1, size_t n);
int		contain(char **array, char *word);
int		ft_isspace(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_xstrdup(const char *s1);

#endif
