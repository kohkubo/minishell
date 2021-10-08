#include "shell.h"

#include "astree.h"

void	expand_astree(t_astree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type & NODE_DATA)
		free_set((void **)&tree->data, minishell_expand(tree->data));
	expand_astree(tree->right);
	expand_astree(tree->left);
}
