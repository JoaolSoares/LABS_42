#include "../include/decoder.h"

/*
 * Transforms a char into a string being the char followed by a '\0'.
 * c - char to convert to string
 * returns a string with char followed by a '\0'
 */
static char	*add_char_in_string(char c)
{
	char *char_str = calloc(2, sizeof(char));

	char_str[0] = c;
	char_str[1] = 0;

	return(char_str);
}

/* 
 * Use the dictionary to decompress the text.
 * encode - compressed text
 * dict - dictionary used for decompress text
 * returns a string descompressed.
 */
char	*text_decoder(char *encode, char **dict)
{
	char	*decode_text = calloc(strlen(encode), sizeof(char));
	int		i = 0;


	while (encode[i])
	{
		for (int j = 0; dict[j]; j++)
		{
			if (strncmp(encode + i, dict[j] + 1, strlen(dict[j]) - 1) == 0)
			{
				char *char_str =  add_char_in_string(dict[j][0]);
				strcat(decode_text, char_str);

				i += strlen(dict[j]) - 1;

				free(char_str);
				break ;
			}
		}
	}

	return (decode_text);
}
