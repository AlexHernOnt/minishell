/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:25:17 by amorion-          #+#    #+#             */
/*   Updated: 2022/02/14 13:27:51 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	If ctl-d frees aux and return 1 to exit the loop
*/

int	ft_ctrld(char *aux)
{
	if (!aux)
	{
		printf("exit\n");
		free(aux);
		return (1);
	}
	return (0);
}

/*
**	If g_id = -1 at the begining: replaces the line by 0 and carries on. 
** Otherwhise g_pid is a blocked process which is terminated
*/

void	ft_ctrl(int sig)
{
	if (sig == 2)
	{
		if (g_id == -1)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf("\n");
			kill(g_id, SIGINT);
		}
	}
	if (sig == 3)
	{
		write(2, "^\\", 2);
		kill(g_id, SIGQUIT);
	}
}

/* Sets the termios c_lflag to not echoctrl so that ^C is not printed*/

void	ft_set_tc(t_tcattr terminal, int reset)
{
	if (reset)
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal.original);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &terminal.ctrl_c);
}

/*Sets terminal configuration */

t_tcattr	ft_tc_config(void)
{
	t_tcattr	tc;

	tcgetattr(STDIN_FILENO, &tc.original);
	tc.ctrl_c = tc.original;
	tc.ctrl_c.c_lflag = ~ECHOCTL;
	return (tc);
}

/* To set the signals and terminal in interaactive mode*/
void	ft_signals(t_tcattr terminal)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl);
	ft_set_tc(terminal, 0);
}
