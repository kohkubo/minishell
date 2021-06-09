#include "astree.h"
#include <stdlib.h>
#include "libft.h"

t_astree	*astree_create_node(
				t_node_type type, char *data, t_astree *left, t_astree *right)
{
	t_astree	*res;

	res = ft_xmalloc(sizeof(t_astree));
	res->type = type;
	res->data = data;
	res->left = left;
	res->right = right;
	return (res);
}

t_astree	*astree_delete_node(t_astree *node)
{
	if (node == NULL)
		return (NULL);
	node->left = astree_delete_node(node->left);
	node->right = astree_delete_node(node->right);
	free(node);
	return (NULL);
}
