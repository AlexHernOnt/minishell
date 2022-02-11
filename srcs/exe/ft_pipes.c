/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:49:17 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 15:00:43 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipes(t_mini *ms)
{
	if (ms->pipe == 1 && ms->p_first == 1 && ms->p_last == 0)
	{
		close(ms->pipes_fds[0][0]);
		dup2(ms->pipes_fds[0][1], 1);
	}
	else if (ms->p_last == 1 && ms->pipe == 1)
	{
		return (ft_middle_pipe(ms));
	}
	else if (ms->p_last == 1)
	{
		ft_finish_pipe(ms);
	}
	return (1);
}

int	ft_middle_pipe(t_mini *ms)
{
	close(ms->pipes_fds[(ms->pipe_to_use) - 1][1]);
	dup2(ms->pipes_fds[(ms->pipe_to_use) - 1][0], 0);
	close(ms->pipes_fds[ms->pipe_to_use][0]);
	dup2(ms->pipes_fds[ms->pipe_to_use][1], 1);
	return (1);
}

void	ft_finish_pipe(t_mini *ms)
{
	close(ms->pipes_fds[(ms->pipe_to_use) - 1][1]);
	dup2(ms->pipes_fds[(ms->pipe_to_use) - 1][0], 0);
	dup2(ms->o_stdout, 1);
	ms->p_done = 1;
	ms->p_last = 0;
}
