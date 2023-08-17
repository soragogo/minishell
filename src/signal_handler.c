#include "minishell.h"
void handler(int signum)
{
		if (signum == SIGQUIT)
		{
				return ;
		}
}


void ft_signals(void)
{
		signal(SIGQUIT, handler);
}
