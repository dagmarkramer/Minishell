#include "minishell.h"

char	*environment_variables(t_mini *mini)
{
	char	*str;
	int	i;
	int	a;

	i = 1;
	a = 0;
	str = getenv(&mini->splitin[i][a + 1]);//getenv from after $ sign
	if (!str)
		return (NULL);
	return (str);
}

// relative path: the hierarchical path that locates a file or folder on a file system starting from the current directory
// absolute path: the complete details needed to locate a file or folder
void	ms_cd(t_mini *mini)
{
	chdir(mini->splitin[1]);
	free2darr(mini);
}

void	ms_pwd(t_mini *mini)
{
	char buf[PATH_MAX];

	(void)mini;
	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
	free2darr(mini);
}

void	ms_export(t_mini *mini)
{
	char **split;
	char **exportvar;

	split = ft_split(mini->input, ' ');
	ev_sort_alfa(mini->env);
	if (split[1])
	{
		exportvar = ft_split(split[1], '=');
		ev_add_env(exportvar[0], exportvar[1], &mini->env);
	}
	else
		ft_printlst(mini->env, "export");
}

void	ms_unset(t_mini *mini)
{
	char **split;
	char **exportvar;

	split = ft_split(mini->input, ' ');
	if (split[1])
	{
		exportvar = ft_split(split[1], '=');
		ev_rem_env(exportvar[0], &mini->env);
	}
}

void	ms_env(t_mini *mini)
{
	ft_printlst(mini->env, "env");
}

