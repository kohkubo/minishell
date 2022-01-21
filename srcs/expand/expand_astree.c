#include "shell.h"

#include "astree.h"

void	expand_astree(t_astree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type & NODE_DATA)
	{
		if (tree->type & NODE_REDIRECT_IN2)
			free_set((void **)&tree->data,
				minishell_expand(tree->data, expand_handler_heredoc));
		else
			free_set((void **)&tree->data,
				minishell_expand(tree->data, expand_handler));
	}
	expand_astree(tree->right);
	expand_astree(tree->left);
}
