#include "../include/encoder.h"

/* 
 * Inserts a new node (leaf) already in its proper place (sorted) in the linked list.
 * list - linked list;
 * new_leaf - new node to be insert in the list.
 */
void	insert_in_list(t_list *list, t_leaf *new_leaf)
{
	t_leaf	*temp_leaf;

	if (list->start == NULL)
		list->start = new_leaf;
	else if (new_leaf->frequency < list->start->frequency)
	{
		new_leaf->next = list->start;
		list->start = new_leaf;
	}
	else
	{
		temp_leaf = list->start;
		while (temp_leaf->next && temp_leaf->next->frequency <= new_leaf->frequency)
			temp_leaf = temp_leaf->next;
		new_leaf->next = temp_leaf->next;
		temp_leaf->next = new_leaf;
	}
	list->size++;
}

/* 
 * Removes the first node(leaf) from the linked list.
 * list - linked list.
 * return the new first node(leaf) from the list.
 */
t_leaf *remove_first_in_list(t_list *list)
{
	t_leaf *temp_leaf = NULL;

	if (list->start)
	{
		temp_leaf = list->start;
		list->start = temp_leaf->next;
		temp_leaf->next = NULL;
		list->size--;
	}

	return (temp_leaf);
}

/* 
 * creates a vector with the size of the ASCII table and
 * stores the number of occurrences of each character in its proper index.
 * data - structure where there is the vector, and the text to be analyzed.
 */
void	create_frequency_tabel(t_data *data)
{
	// Vector initialized with size of the ascii table, to store the occurrence of each character in the text.
	for (int i = 0; i < 256; i++)
		data->vet[i] = 0;

	// Each appearance of a character is marked in its respective position in the vector
	for (int i = 0; data->text[i]; i++)
		data->vet[data->text[i]]++;
}

/* 
 * Create a list based on the frequency of each character to organize them in ascending order.
 * data - structure that has stored the frequency of each character;
 * list - struct made for a linked list, which will be the increasing frequency list.
 */
void	create_list(t_data *data, t_list *list)
{
	t_leaf	*new_leaf;

	list->start = NULL;
	list->size = 0;

	for (int i = 0; i < 256; i++)
	{
		//Cchecks if it has at least one appearance in the text.
		if (data->vet[i] > 0)
		{
			new_leaf = malloc(sizeof(t_leaf));
			if (!new_leaf)
				exit(30);

			// Add a new node in the linked list.
			new_leaf->character = i;
			new_leaf->frequency = data->vet[i];
			new_leaf->right = NULL;
			new_leaf->left = NULL;
			new_leaf->next = NULL;

			insert_in_list(list, new_leaf);
		}
	}
}
