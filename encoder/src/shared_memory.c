#include "../include/encoder.h"

/* 
 * Receives the encoder message through shared memory;
 * returns a string read from a shared memory block.
 */
char	*receive_mensage(void)
{
	char	*mensage;
	key_t	key = ftok("shared_memory.c", 0);
	int		shmid = shmget(key, sizeof(char *), 0644 | IPC_EXCL);

	// Attach the block;
	mensage = shmat(shmid, NULL, 0);
	char *mensage_dup = ft_strdup(mensage);

	// Kill the block.
	shmdt((void *) mensage);
	shmctl(shmid, 0, NULL);

	return (mensage_dup);
}

/* 
 * opens a shared block in memory, and sends a string.
 * text - string to be shared.
 */
void	share_mensage(char *text)
{
	char	*mensage;
	key_t	key = ftok("shared_memory.c", 0);
	int		shmid = shmget(key, sizeof(char) * (strlen(text) + 1), 0644 | IPC_CREAT);

	mensage = (char *)shmat(shmid, NULL, 0);
	strcpy(mensage, text);

	shmdt((void *)mensage);
}

/* 
 * Prepares the dictionary and the compressed string to be sent via shared memory to the decoder.
 * both are joined into just one string
 * text - encoded text;
 * dictionary - dictionary.
 * returns a string with compressed text and dictionary.
 */
char	*prepare_mensage(char *text, char **dictionary)
{
	char	*msg;
	int		msg_size = strlen(text) + 1;

	// Calculates the size of the final message.
	for (int i = 0; i < 256; i++)
		if (strlen(dictionary[i]) > 0)
			msg_size += (strlen(dictionary[i]) + 2);

	msg = calloc(msg_size + 1, sizeof(char *));

	// Add encode text to message.
	strcpy(msg, text);
	strcat(msg, " ");
	// add dictionary in message.
	for (int i = 0; i < 256; i++)
	{
		if (strlen(dictionary[i]) > 0)
		{
			msg[strlen(msg)] = i;
			msg[strlen(msg) + 1] = 0;
			strcat(msg, dictionary[i]);
			strcat(msg, " ");
		}
	}
	return (msg);
}

