#include "../include/encoder.h"

/* 
 * Get the user option to know whether or not to run the Decoder next.
 * returns 1 - if you want to run the decoder;
 * returns 2 - if you don't want to run the decoder;
 * If the response is invalid, the program is exited giving an error output.
 */
int user_option(void)
{
	char opt = 0;

	printf("Do you want to run Decoder next?\n[Y] or [N]\n> ");
	scanf("%c", &opt);

	if (opt == 'Y' || opt == 'y')
		return (1);
	else if (opt == 'N' || opt == 'n')
		return (2);
	else
	{
		ft_putstr_fd("ERRO! this is not a valid option, try again...\n> ", STDERR_FILENO);
		exit (5);
	}
}

int main(int argc, char *argv[])
{
	t_data	*data;
	t_list	*list;
	t_leaf	*tree;

	// ARGC VALIDATION
	if (argc < 2)
	{
		ft_putstr_fd("ERROR! Number of arguments invalid!\n", STDERR_FILENO);
		exit (1);
	}

	// RECIEVE MENSAGE.
	if (!strcmp(argv[1], "1a9**987-1") && !strcmp(argv[2], "process infos") && !strcmp(argv[3], "98-701@12"))
	{
		char *process_infos = receive_mensage();
		print_process_infos(process_infos);
		exit(0);
	}

	int opt = user_option();

	data = malloc(sizeof(t_data));
	if (!data)
		exit(2);

	// OPEN AND READ FILES
	read_files(data, argc - 1, argv + 1);

	// FREQUENCY LIST
	list = malloc(sizeof(t_list));
	if (!list)
		exit(3);
	create_frequency_tabel(data);
	create_list(data, list);

	// TREE
	tree = create_tree(list);

	// DICTIONARY
	data->dictionary = malloc(sizeof(char *) * 256);
	for (int i = 0; i < 256; i++)
		data->dictionary[i] = calloc(tree_size(tree) + 1, sizeof(char));
	create_dictionary(data->dictionary, tree, "", tree_size(tree));

	// ENCODE
	data->encode_text = encode(data->text, data->dictionary);

	// SHARED MEMORY
	char *mensage = prepare_mensage(data->encode_text, data->dictionary);
	share_mensage(mensage);

	// USER OPTION
	if (opt == 1)
		system("./Decoder");
	else
		printf("Encoded text:\n%s\n", data->encode_text);

	// FREES
	free_all(data, list, tree, data->dictionary);
	free(mensage);

	return (0);
}
