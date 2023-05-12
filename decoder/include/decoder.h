#ifndef DECODER_H
# define DECODER_H

//	INCLUDES
#include "../../lib/include/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 

//	STRUCTS
typedef struct s_data
{
	char	*mensage;
	char	*text;
	char	*tmp_dict;
	char	**dictionary;
	char	*decode_text;

}	t_data;

char	*receive_mensage(void);
void	share_mensage(char *text, char *time, char *bits_before);

void	separate_mensage(t_data *data);

char	**decode_dict(char *tmp_dict);
char	*text_decoder(char *encode, char **dict);

#endif