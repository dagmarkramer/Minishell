#include "minishell.h"

void	fd_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	fd_replacer(int *to_replace, int new_fd)
{
	fd_close(*to_replace);
	*to_replace = new_fd;
}

// O_RDWR O_RDONLY O_WRONLY O_APPEND
void	fd_open_and_replace(int *to_replace, char *filename, int openflags)
{
	int	new_fd;

	new_fd = open(filename, openflags, 0666);
	if (*to_replace > 2)
		close(*to_replace);
	if (new_fd != -1)
		*to_replace = new_fd;
}

void	fd_redirect(t_execute *info, int index)
{
	if (ft_strncmp(info->arg[index], "<<", 2) == 0)
		fd_replacer(&(info->fd_input), ms_heredoc(info->arg[index + 1]));
	else if (ft_strncmp(info->arg[index], ">>", 2) == 0)
		fd_open_and_replace(&(info->fd_output), info->arg[index + 1], O_APPEND | O_CREAT);
	else if (ft_strncmp(info->arg[index], ">", 1) == 0)
		fd_open_and_replace(&(info->fd_output), info->arg[index + 1], O_WRONLY | O_CREAT);
	else
		fd_open_and_replace(&(info->fd_input), info->arg[index + 1], O_RDONLY);
	free(info->arg[index]);
	free(info->arg[index + 1]);
	info->arg[index] = NULL;
	info->arg[index + 1] = NULL;
	while (info->arg[index + 2] != NULL)
	{
		info->arg[index] = info->arg[index + 2];
		index++;
	}
	info->arg[index] = NULL;
}

char	**fd_redirections(t_execute *info)
{
	int	i;

	i = 0;
	while (info->arg[i] != NULL)
	{
		if (info->arg[i][0] == '<' || info->arg[i][0] == '>')
			fd_redirect(info, i);
		i++;
	}
	return (info->arg);
}
