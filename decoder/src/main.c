#include "../include/decoder.h"

/* 
 * Free all memory allocs.
 */
void	free_all(t_data *data)
{
	free(data->mensage);
	free(data->text);
	free(data->decode_text);
	free(data->tmp_dict);

	for(int i = 0; data->dictionary[i]; i++)
		free(data->dictionary[i]);
	free(data->dictionary);

	free(data);
} 	

int main(void)
{
	t_data	*data;

	// Execution time.
	double time_spent = 0.0;
    	clock_t begin = clock();

	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);

	// Pick the mensage in shared memory.
	data->mensage = receive_mensage();

	// separates the compressed text from the dictionary.
	separate_mensage(data);

	// Convert dictionary to matrix.
	data->dictionary = decode_dict(data->tmp_dict);

	// Decode compressed text.
	data->decode_text = text_decoder(data->text, data->dictionary);

	// Execution time.
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	char time_in_string[20];
	sprintf(time_in_string, "%f", time_spent);

	// Share mensage to encoder.
	char *bits_before = ft_itoa(strlen(data->text));
	share_mensage(data->decode_text, time_in_string, bits_before);

	// FREES
	free_all(data);
	free(bits_before);

	// Call de Encoder.
	system("./Encoder 1a9**987-1 \"process infos\" 98-701@12");

	return (0);
}
