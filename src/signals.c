#include <signal.h>
#include <unistd.h>
#include "minishell.h"

void	newline_handler(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	nothing_handler(int signum)
{
	(void)signum;
	rl_redisplay();
}

int signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, newline_handler);
	signal(SIGQUIT, nothing_handler);
	return (0);
}
