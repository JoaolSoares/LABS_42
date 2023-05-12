#ifndef ENCODER_H
# define ENCODER_H

//	INCLUDES
#include "../../lib/include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

//	STRUCTS
typedef struct s_data
{
	unsigned char	*text;
	int				vet[256];
	char			**dictionary;
	char			*encode_text;

}	t_data;

typedef struct s_leaf
{
	unsigned char	character;
	int				frequency;
	struct s_leaf	*right;
	struct s_leaf	*left;
	struct s_leaf	*next;

}	t_leaf;

typedef struct s_list
{
	t_leaf	*start;
	int		size;

}	t_list;


void	read_files(t_data *data, int num_files, char *files[]);

void	print_process_infos(char *process_infos);

void	create_frequency_tabel(t_data *data);
void	create_list(t_data *data, t_list *list);
void	insert_in_list(t_list *list, t_leaf *new_leaf);
t_leaf	*remove_first_in_list(t_list *list);

t_leaf	*create_tree(t_list *list);
int		tree_size(t_leaf *tree);

void	create_dictionary(char **dictionary, t_leaf *tree, char *binary, int size);
char	*encode(char *text, char **dictionary);

char	*prepare_mensage(char *text, char **dictionary);
char	*receive_mensage(void);
void	share_mensage(char *text);

void	free_all(t_data *data, t_list *list, t_leaf *tree, char **dictionary);

#endif