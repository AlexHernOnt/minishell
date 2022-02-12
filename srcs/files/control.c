/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:25:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/28 17:06:41 by ahernand         ###   ########.fr       */
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

struct termios	ft_tc_config(t_tcattr terminal)
{
	struct termios new;
	new = terminal.original;
	new.c_lflag = ~ECHOCTL;
	return(new);
}
