#include "astree.h"
#include "libex.h"

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

/**
 * @brief delete node.
 * @return always NULL.
 */
t_astree	*astree_delete_node(t_astree *node)
{
	if (node == NULL)
		return (NULL);
	node->left = astree_delete_node(node->left);
	node->right = astree_delete_node(node->right);
	free(node->data);
	free(node);
	return (NULL);
}

t_astree	*astree_get_right_last(t_astree *node)
{
	while (node->right != NULL)
		node = node->right;
	return (node);
}
