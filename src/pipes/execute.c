#include "minishell.h"

typedef struct	s_execute
{
	char		**arg;
	char		**env;
	int			fd_input;
	int			fd_output;
}				t_execute;

char	**get_path_options(t_list *envlst)
{
	char	**paths;
	char	*unsplit;

	unsplit = ev_getenv("PATH", envlst); // malloced in linked list so do not need to free
	if (unsplit == NULL)
		return (NULL); // exception
	paths = ft_split(unsplit, ':');
	ft_malloc_fail_check(paths);
	return (paths);
}

// this takes place in a child function (forked)
// only for non buildins that do not have an absolute path
void	ft_execute_relative(t_execute *exe_info, t_list *envlst)
{
	char	**paths;
	char	*pathjoined;
	char	*tmp;
	int		i;

	i = 0;
	paths = get_path_options(envlst);
	if (paths == NULL)
		exit(127);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		ft_malloc_fail_check(pathjoined);
		pathjoined = ft_strjoin(tmp, exe_info->arg[0]);
		ft_malloc_fail_check(pathjoined);
		free(tmp);	// not needed actually because execve wil free everything or exit will do it later
		execve(pathjoined, exe_info->arg, exe_info->env);	// run execve without envp?
		i++;
	}
	exit(127);
}

void	ft_execute_absolute(t_execute *exe_info)
{
	execve(exe_info->arg[0], exe_info->arg, exe_info->env);	// run execve without envp?
	exit(127);
}

int	exe_fork(t_execute *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		ft_disruptive_exit("fork failed", 43);
	if (pid == 0)
		exe_child_process();
	waitpid(pid, &status, 0);
	return(WEXITSTATUS(status));
}

// arg is al gezet
// env wordt hier gezet (in de child functie?)
// fd input en output zijn al gezet
void	exe_pre_fork(t_execute *exe_info)
{
	// pipes are handled before this by the pipe fuctions, if there are redirecitons the pipe gets overwritten but first closed.
	// strip args of redirections and overwrite the i/o fds

	// then call the funciton where we fork and call the exec function!
	return (exe_fork(exe_info));
}
