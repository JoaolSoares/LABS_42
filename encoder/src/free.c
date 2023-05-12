#include "../include/encoder.h"

/* 
 * Free all dictionary.
 */
static void	free_dictionary(char **dictionary)
{
	for (int i = 0; i < 256; i++)
		free(dictionary[i]);
	free(dictionary);
}

/* 
 * Free all elements of Huffman tree.
 */
static void	free_tree(t_leaf *tree, int size)
{
	t_leaf *temp_leaf;

	temp_leaf = tree;
	if (temp_leaf->left && temp_leaf->right)
	{
		free_tree(temp_leaf->right, size + 1);
		free_tree(temp_leaf->left, size + 1);
	}
	if (size)
		free(tree);
}

/* 
 * Free all elements of linked list.
 */
static void	free_list(t_list *list)
{
	t_leaf *aux = list->start;
	t_leaf *aux_next = aux->next;

	while(aux && aux_next)
	{
		free(aux);
		aux = aux_next;
		aux_next = aux->next;
	}
	free(aux);
	free(list);
}

/* 
 * Free all memory allocs.
 */
void	free_all(t_data *data, t_list *list, t_leaf *tree, char **dictionary)
{
	free_dictionary(dictionary);
	free_tree(tree, 0);
	free_list(list);
	free(data->text);
	free(data->encode_text);
	free(data);
}
