/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:01:50 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/29 13:14:59 by kohkubo          ###   ########.fr       */
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
size_t	ft_min_size_t(size_t a, size_t b);
void	free_set(void **dst, void *src);
void	*ft_xmalloc(size_t size);
void	ft_fatal(const char *emsg);
void	ft_error_exit(const char *emsg);
void	*ft_xcalloc(size_t count, size_t size);
char	*ft_strndup(const char *s1, size_t n);
int		contain(char **array, char *word);
int		ft_isspace(int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_xstrdup(const char *s1);
bool	is_space_string(char *s);
size_t	spacelen(char *s);
int		arraylen(char **array);
void	print_array(char **array);
char	*random_string(size_t size);
char	**str_arraydup(char **array);
int		debug_arraycmp(char **aa, char **bb);
bool	is_num_string(char *s);
long	ft_atol(const char *s);

#endif
