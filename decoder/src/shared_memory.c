#include "../include/decoder.h"

/* 
 * creates a message with all process information to send it to the encoder via shared memory
 * text - decompressed text;
 * time - the execution time from decoder;
 * bits_before - amount of bits before de descompression.
 */
void	share_mensage(char *text, char *time, char *bits_before)
{
	char	*mensage;
	key_t	key = ftok("shared_memory.c", 0);
	int		shmid = shmget(key, sizeof(char) * (strlen(text) + strlen(time) + strlen(bits_before) + 1), 0644 | IPC_CREAT);

	mensage = (char *)shmat(shmid, NULL, 0);
	
	strcat(bits_before, " ");
	strcpy(mensage, bits_before);
	strcat(time, " ");
	strcat(mensage, time);
	strcat(mensage, text);

	shmdt((void *)mensage);
}

/* 
 * Receives the encoder message through shared memory;
 * returns a string read from a shared memory block.
 */
char	*receive_mensage(void)
{
	char	*mensage;
	char	*mensage_dup;
	key_t	key = ftok("shared_memory.c", 0);
	int		shmid = shmget(key, sizeof(char *), 0644 | IPC_EXCL);

	// Attach the block;
	mensage = shmat(shmid, NULL, 0);
	mensage_dup = ft_strdup(mensage);

	// Kill the block.
	shmdt((void *) mensage);

	return(mensage_dup);
}
