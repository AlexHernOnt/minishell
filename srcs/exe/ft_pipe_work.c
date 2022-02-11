/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_work.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:48:28 by ahernand          #+#    #+#             */
/*   Updated: 2022/02/10 15:48:29 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_close_all_fd(t_mini *ms)
{
	int	i;

	i = 0;
	while (ms->pipes_fds[i] != NULL)
	{
		close(ms->pipes_fds[i][0]);
		close(ms->pipes_fds[i][1]);
		i++;
	}
}

void	ft_pipes_opening(t_mini *ms, t_line **ptr)
{
	int		i;
	int		j;
	t_line	*original;

	i = 0;
	j = 0;
	original = (*ptr);
	ms->pipe_to_use = 0;
	while ((*ptr) != NULL)
	{
		if ((*ptr)->type == 5)
			i++;
		(*ptr) = (*ptr)->next;
	}
	(*ptr) = original;
	ms->pipes_fds = malloc((sizeof(int *)) * (i + 1));
	while (j < i)
	{
		ms->pipes_fds[j] = malloc(sizeof(int) * 2);
		pipe(ms->pipes_fds[j]);
		j++;
	}
	ms->pipes_fds[i] = NULL;
}

void	ft_start_pipe(t_mini *ms, t_line **ptr)
{
	int		i;
	t_line	*original;

	i = 0;
	ft_pipes_opening(ms, ptr);
	original = (*ptr);
	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) != NULL && (*ptr)->type == 5)
	{
		(*ptr) = (*ptr)->next;
		ms->pipe = 1;
		ms->p_first = 1;
	}
	(*ptr) = original;
}

/*
**		Find the pipe locations
*/

void	ft_pipe_location(t_mini *ms, t_line **ptr)
{
	if ((*ptr) != NULL && (*ptr)->type == 5)
	{
		ms->pipe = 1;
		ms->p_last = 1;
	}
	else if ((*ptr) == NULL && ms->pipe)
	{
		ms->pipe = 0;
		ms->p_last = 1;
	}
}

void	ft_next_pipe(t_mini *ms, t_line **ptr)
{
	int		i;
	t_line	*save;

	i = 0;
	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) != NULL && (*ptr)->type == 5)
	{
		(*ptr) = (*ptr)->next;
		ms->pipe_to_use++;
	}
	save = (*ptr);
	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		(*ptr) = (*ptr)->next;
	}
	ft_pipe_location(ms, ptr);
	(*ptr) = save;
}
