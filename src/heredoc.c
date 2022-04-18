#include "minishell.h"

/*
 *	create tmp files for heredoc or directly send info into pipe
 */

/*
 *	return the open fd to read from from pipe!
 *	if the heredoc is disrupted the fd will be closed and nothing will be available to read
 */

char	*ft_stradd(char *str1, char *str2)
{
	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL && str2 != NULL)
		return (str2);
	if (str1 != NULL && str2 == NULL)
		return (str1);
	return (ft_strjoin(str1, str2));
}

char	*ft_stradd_with_newline(char *str1, char *str2)
{
	char	*tmp;
	char	*ret;

	tmp = ft_stradd(str1, str2);
	if (tmp == NULL)
		return (NULL);
	ret = ft_stradd(tmp, "\n");
	free(tmp);
	return (ret);
}

void	child_process(int writefd, char *delimiter)
{
	char	*line;
	char	*final_product;
	char	*tmp;
	int		gnl_return;
	//  signal handling
	//	ignore signals that need to be ignored

	final_product = NULL;
	gnl_return = 1;
	while (gnl_return)
	{
		gnl_return = get_next_line(0, &line);
		if (gnl_return == -1)
			exit(1);
		if (ft_strncmp(line, delimiter, (size_t)ft_strlen(delimiter) + 1) == 0)
		{
			ft_putstr_fd(final_product, writefd);
			exit(0);
		}
		tmp = final_product;
		final_product = ft_stradd_with_newline(final_product, line);
		ft_malloc_fail_check(final_product);
		if (tmp != NULL)
			free(tmp);
	}
	ft_putstr_fd(final_product, writefd);
	exit(0);
}

int	ms_heredoc(char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	printf("heredoc\n");
	if (pipe(pipefd))
		ft_disruptive_exit("pipefd failed", 42);
	pid = fork();
	if (pid == -1)
		ft_disruptive_exit("fork failed", 43);
	if (pid == 0)
	{
		close(pipefd[READ]);
		child_process(pipefd[WRITE], delimiter);
	}
	close(pipefd[WRITE]);
	waitpid(pid, &status, 0);
	if(WIFSIGNALED(status))
		close(pipefd[READ]);
	if(WEXITSTATUS(status) == 1)
		ft_disruptive_exit("gnl failed", 44);
	return (pipefd[READ]);
}
 