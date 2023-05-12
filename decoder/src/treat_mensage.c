#include "../include/decoder.h"

/* 
 * finds and returns the position of the space, so as not to conflict when splitting.
 * Stores the position of the space and replaces it with an 'x' to, after the split performed, replace it again with an ' '.
 * str - dicitonary.
 * reurns the positions of the space in dictionary
 */
static int	locate_space(char *str)
{
	int i = 0;
	int space = -1;
	int	position_space = 0;

	while (str[i])
	{
		if (strncmp(str + i, "  ", 2) == 0)
		{
			space = i;
			break ;
		}
		i++;
	}

	if (space != -1)
	{
		str[space + 1] = 'x';
		i = 0;
		while (i < space)
		{
			if (str[i] == ' ')
				position_space++;
			i++;
		}
	}
	else
		return (-1);

	return (position_space);
}

/* 
 * Turns the string dictionary into a matrix.
 * tmp_dict - dictionary in string form.
 * returns a matrix that represents the dictionary.
 */
char	**decode_dict(char *tmp_dict)
{
	char	**dictionary;
	int		space;

	space = locate_space(tmp_dict);
	dictionary = ft_split(tmp_dict, ' ');
	if (space >= 0)
		dictionary[space][0] = ' ';

	return(dictionary);
}

/* 
 * Separates the message received by the encoder into text(compressed text) and tmp_dict(string dictionary).
 * data - structure that will store the data.
 */
void	separate_mensage(t_data *data)
{
	int	i;

	for (i = 0; data->mensage[i] != ' '; i++) ;
	
	// Compressed text.
	data->text = calloc(i + 1, sizeof(char));
	data->text = strncpy(data->text, data->mensage, i);

	// String dictionary.
	data->tmp_dict = calloc((strlen(data->mensage) - strlen(data->text)) + 1, sizeof(char));
	data->tmp_dict = strcpy(data->tmp_dict, data->mensage + i);
}
