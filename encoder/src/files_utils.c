#include "../include/encoder.h"

/* 
 * Take a array of files(strings) and open his fds.
 * num_files - Amount of files;
 * files - array with all files;
 * returns a array of all fds opened.
 */
static int	*open_fds(int num_files, char *files[])
{
	int	*fd;
	int	i = -1;

	fd = calloc(num_files, sizeof(int));

	while (++i < num_files)
	{
		fd[i] = open(files[i], O_RDONLY);
		if (fd[i] < 0)
		{
			while (--i > 0)
				close(fd[i]);
			ft_putstr_fd("ERROR! Problem opening files!\n", STDERR_FILENO);
			fd[0] = -1;
			return (fd);
		}
	}

	return (fd);
}

/*
 * Take a array of files(strings) and joins all the texts in just one string.
 * data - structure that has the variable text, which is where the text of all the files will be stored, separating them with a '\n';
 * num_files - Amount of files;
 * files - array with all files;
 */
void	read_files(t_data *data, int num_files, char *files[])
{
	int	*fd;

	// Open fds.
	fd = open_fds(num_files, files);
	if (fd[0] == -1)
	{
		free(fd);
		free(data);
		exit (20);
	}

	// get the content of all fds.
	int i = -1;
	data->text = NULL;
	while (++i < num_files)
	{
		char *buffer = get_next_line(fd[i]);
		while (buffer)
		{
			data->text = ft_strjoin(data->text, buffer);
			free(buffer);
			buffer = get_next_line(fd[i]);
		}
		close(fd[i]);
		if (i < num_files - 1)
			data->text = ft_strjoin(data->text, "\n");
	}

	free(fd);
}
