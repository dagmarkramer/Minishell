#include "minishell.h"

void	error_handling(char *errormessage)
{
	perror(errormessage);
}

void	free2darr(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->splitin[i])
	{
		free (mini->splitin[i]);
		i++;
	}
	free (mini->splitin);
}

void	ms_redirect(t_mini *mini, char *c)
{
	int	fd;
	// struct stat *buf;
	// int	ret;
	// int	i;
	// char	*line;

	(void)mini;
	if (!ft_strncmp(">>", c, ft_strlen("c")))
	{
		fd = open("outfile", O_WRONLY | O_APPEND);
		if (fd == -1)
			error_handling("outfile");
		if (dup2(fd, 0) == -1)
			error_handling("dup2() error");
	}
	else if (!ft_strncmp("<", c, ft_strlen("c")))
	{
		printf("hi");
		fd = open("infile", O_RDONLY);
		if (fd == -1)
			error_handling("infile");
		if (dup2(fd, 1) == -1)
			error_handling("dup2() error");
	}
	else if (!ft_strncmp(">", c, ft_strlen("c")))
	{
		printf("hi2");
		fd = open("outfile",  O_WRONLY | O_CREAT, 0666);
		if (fd == -1)
			error_handling("outfile");
		if (dup2(fd, 0) == -1)
			error_handling("dup2() error");
	}

	free2darr(mini);
	
}

void	ms_next(t_mini *mini)	// mag blijven
{

	// function [] = {
	// 	"echo" = &ms_ech(mini);
	// 	"pwd" = dhhd;
	// 	int i;
	// 	while()
	// }
		// mini->splitin = ms_tokenizer(mini->input);
		if (!ft_strncmp(mini->splitin[0], "echo", ft_strlen(mini->splitin[0])))
		{
			// ms_echo(mini, newenv);
			return ;
		}
		// if (!ft_strncmp(mini->splitin[0], "pwd", ft_strlen(mini->splitin[0])))
		// 	ms_pwd(mini);
		// if (!ft_strncmp(mini->splitin[0], "cd", ft_strlen(mini->splitin[0])))
		// 	ms_cd(mini);
		// if (!ft_strncmp(mini->splitin[0], "export", ft_strlen(mini->splitin[0])))
		// 	ms_export(mini);
		// if (!ft_strncmp(mini->splitin[0], "unset", ft_strlen(mini->splitin[0])))
		// 	ms_unset(mini);
		// if (!ft_strncmp(mini->splitin[0], "env", ft_strlen(mini->splitin[0])))
		// 	ms_env(mini);
		// if (!ft_strncmp(mini->splitin[0], "exit", ft_strlen(mini->splitin[0])))
		// 	ms_exit(mini);
		// if (!ft_strncmp(mini->splitin[0], "<", ft_strlen(mini->splitin[0])))
		// 	ms_redirect(mini, "<");
		// if (!ft_strncmp(mini->splitin[0], ">", ft_strlen(mini->splitin[0])))
		// 	ms_redirect(mini, ">");
		if (!ft_strncmp(mini->splitin[0], ">>", ft_strlen(mini->splitin[0])))
			ms_redirect(mini, ">>");
}

void	ms_print_word(void *ptr)	// mag blijven
{
	t_token	*token;

	token = (t_token *)ptr;
	printf("%s\n", token->word);
}

void	ms_one_row(t_mini *data)	// mag blijven
{
	t_list	*tokens;

	tokens = ms_tokenizer(data->input, data->env);
	if (tokens == NULL)
		return ;
	ft_lstiter(tokens, ms_print_word);
}

int	ms_init(t_mini *mini, int argc, char **argv, char **newenv)	// mag blijven
{
	// extern char**environ;

	(void)argv;
	mini->input = NULL;
	mini->environ = newenv;
	if (argc != 1)
	{
		printf("Error\nDo not use arguments, a prompt will pop up.\n");
		return (1);
	}
	mini->env = ev_init_env(newenv);
	if (mini->env == NULL)
		return (1);
	ms_signals();
	return (0);
}

void	ms_exit(t_mini *mini)	// mag blijven
{
	ft_lstclear(&mini->env, ev_del_keyval);
	rl_clear_history();
	printf("exit\n");
}

int	main(int argc, char **argv, char **newenv)	// mag blijven
{
	t_mini	mini;

	if (ms_init(&mini, argc, argv, newenv))
		return (1);
	
	// ft_printlst(mini.env);
	// ev_sort_alfa(mini.env);
	// ft_printlst(mini.env);
	
	while (1)
	{
		mini.input = readline("Oud Getrouwd Shell : ");
		if (mini.input == 0 || !ft_strncmp(mini.input, "exit", 5))
			break ;
		if (mini.input[0] != 0)
		{
			add_history(mini.input);
			ms_one_row(&mini);
			// mini.splitin = ms_tokenizer(mini.input);
			// if (!ft_strncmp(mini.input, "env", ft_strlen("env"))) // plus 1? for null terminator '\0'
			// 	ms_env(&mini);
			// if (!ft_strncmp(mini.input, "export", ft_strlen("export")))
			// 	ms_export(&mini);
			// if (!ft_strncmp(mini.input, "unset", ft_strlen("unset")))
				// ms_unset(&mini);
			// ms_next(&mini);
		}
	}
	ms_exit(&mini);
	return (0);
}
