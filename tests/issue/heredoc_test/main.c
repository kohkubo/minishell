/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:50:29 by kohkubo           #+#    #+#             */
/*   Updated: 2021/08/19 14:58:19 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_shell	g_shell;

void	display_lexer(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	printf("%s : %d\n", tok->data, tok->type);
}

void	test(t_lexer *lexer)
{
	printf(" === test ===\n");
	printf("lexer->len : %d\n", lexer->len);
	ft_lstiter(lexer->listtok, display_lexer);
	lexer_free(&lexer);
}

int	main(void)
{
	char	*input;
	t_lexer	*lexer;

	input = NULL;
	while (1)
	{
		input = readline(PROMPT);
		if (input == NULL || ft_strlen(input) == 0)
		{
			free_set((void **)&input, NULL);
			break ;
		}
		add_history(input);
		minishell_lexer(input, &lexer);
		test(lexer);
		free_set((void **)&input, NULL);
	}
	return (0);
}
