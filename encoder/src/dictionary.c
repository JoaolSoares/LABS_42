#include "../include/encoder.h"

/* 
 * Traverse binary tree storing in a string matrix its "translation" in binary.
 * dictionary - array of strings that will store the dictionary;
 * tree - Huffman tree root;
 * binary - an empty string that is added 0 or 1 in the recursion to form the binary code;
 * size - tree size.
 */
void	create_dictionary(char **dictionary, t_leaf *tree, char *binary, int size)
{
	char	left[size];
	char	right[size];

	if (!tree->left && !tree->right)
		strcpy(dictionary[tree->character], binary);
	else
	{
		strcpy(left, binary);
		strcpy(right, binary);

		// Add the respective path number.
		strcat(left, "0");
		strcat(right, "1");

		// Calls the function again to traverse the entire tree.
		create_dictionary(dictionary, tree->left, left, size);
		create_dictionary(dictionary, tree->right, right, size);
	}
}

/* 
 * Use the dictionary to compress a text.
 * text - text to be compress;
 * dicitonary - dictionary.
 * returns the encoded string.
 */
char	*encode(char *text, char **dictionary)
{
	char *encode_text;
	int encode_size = 1;
	int i = -1;

	while (text[++i])
		encode_size += strlen(dictionary[text[i]]);

	encode_text = calloc(encode_size, sizeof(char));
	if (!encode_text)
		exit(60);

	i = -1;
	while(text[++i])
		strcat(encode_text, dictionary[text[i]]);

	return (encode_text);
}
