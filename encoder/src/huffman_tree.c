#include "../include/encoder.h"

/* 
 * Use the frequency list to join nodes and thus create the huffman tree.
 * list - linked frequency list;
 * returns a pointer for a tree root node.
 */
t_leaf	*create_tree(t_list *list)
{
	t_leaf	*leaf_one;
	t_leaf	*leaf_two;
	t_leaf	*new_leaf;

	while (list->size > 1)
	{
		// Removes the first two from the list to create a node.
		leaf_one = remove_first_in_list(list);
		leaf_two = remove_first_in_list(list);

		new_leaf = malloc(sizeof(t_leaf));
		if (!new_leaf)
			exit (40);

		// Add a new node in the linked list.
		new_leaf->frequency = leaf_one->frequency + leaf_two->frequency;
		new_leaf->left = leaf_one; 
		new_leaf->right = leaf_two;
		new_leaf->next = NULL;

		insert_in_list(list, new_leaf);
	}

	return (list->start);
}

/* 
 * Calculate the size of Huffman tree.
 * tree - pointer for tree root.
 * returns the size of tree.
 */
int	tree_size(t_leaf *tree)
{
	int	left;
	int	right;

	if (!tree)
		return (-1);
	else
	{
		// Traverse the entire tree through recursion.
		left = tree_size(tree->left) + 1;
		right = tree_size(tree->right) + 1;

		// Returns the biggest branch.
		if (left > right)
			return (left);
		return (right);
	}
}
