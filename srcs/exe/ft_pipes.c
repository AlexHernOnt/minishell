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
	if (ms->pipe == 1 && ms->p_first == 1)
	{
	//	if (pipe(ms->pipe_fd_a) < 0)
	//		return (ft_error(ms, 150, NULL));
		dup2(ms->pipe_fd_a[1], 1);
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
	if (ms->p_using == 'a')
	{
		close(ms->pipe_fd_a[1]);
		dup2(ms->pipe_fd_a[0], 0);
		if (pipe(ms->pipe_fd_b) < 0)
			return (ft_error(ms, 150, NULL));
		ms->p_b_exists = 1;
		dup2(ms->pipe_fd_b[1], 1);
		ms->p_using = 'b';
	}
	else if (ms->p_using == 'b')
	{
		close(ms->pipe_fd_b[1]);
		close(ms->pipe_fd_a[0]);
		dup2(ms->pipe_fd_b[0], 0);
		if (pipe(ms->pipe_fd_a) < 0)
			return (ft_error(ms, 150, NULL));
		dup2(ms->pipe_fd_a[1], 1);
		ms->p_using = 'a';
	}
	return (1);
}

void	ft_finish_pipe(t_mini *ms)
{
	if (ms->p_using == 'a')
	{
		close(ms->pipe_fd_a[1]);
		if (ms->p_b_exists == 1)
			close(ms->pipe_fd_b[0]);
		dup2(ms->pipe_fd_a[0], 0);
		dup2(ms->o_stdout, 1);
	}
	else if (ms->p_using == 'b')
	{
		close(ms->pipe_fd_a[0]);
		if (ms->p_b_exists == 1)
			close(ms->pipe_fd_b[1]);
		dup2(ms->pipe_fd_b[0], 0);
		dup2(ms->o_stdout, 1);
	}
	ms->p_done = 1;
	ms->p_last = 0;
}
