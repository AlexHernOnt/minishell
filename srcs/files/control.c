/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:25:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/27 16:48:25 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	If ctl-d frees aux and return 1 to exit the loop
*/

int	ft_ctrld(char *aux, t_mini *ms)
{
	if (!aux)
	{
		printf("\n");
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
	printf("\n");
	if (sig == 2)
	{
		if (g_id == -1)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else
		kill(g_id, SIGINT);
	if (sig == 3 && g_id != -1)
		kill(g_id, SIGQUIT);
}
