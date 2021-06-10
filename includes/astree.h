#ifndef ASTREE_H
# define ASTREE_H

typedef enum e_node_type
{
	NODE_PIPE 			= (1 << 0),
	NODE_BCKGRND 		= (1 << 1),
	NODE_SEQ 			= (1 << 2),
	NODE_REDIRECT_IN	= (1 << 3),
	NODE_REDIRECT_OUT	= (1 << 4),
	NODE_REDIRECT_IN2	= (1 << 5),
	NODE_REDIRECT_OUT2	= (1 << 6),
	NODE_CMDPATH		= (1 << 7),
	NODE_ARGUMENT		= (1 << 8),
	NODE_DATA 			= (1 << 9),
	NODE_REDIRECT_LIST	= (1 << 10),
	NODE_REDIRECTION	= (1 << 11),
}	t_node_type;

/*
** Deliverables of parse.
*/
typedef struct s_astree
{
	t_node_type		type;
	char			*data;
	struct s_astree	*left;
	struct s_astree	*right;
}	t_astree;

t_astree	*astree_create_node(
				t_node_type type, char *data, t_astree *left, t_astree *right);
t_astree	*astree_delete_node(t_astree *node);
t_astree	*astree_get_right_last(t_astree *node);

#endif
