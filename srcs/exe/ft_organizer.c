/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:07 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 17:00:51 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		ft_organizer
*/

int	ft_in_fork(t_mini *ms, t_line **ptr, int *i)
{
	int		u;

	u = 0;
	while (ms->pipes_fds[u] != NULL)
	{
		if (u == ms->pipe_to_use || u == ms->pipe_to_use - 1)
		{
		}
		else
		{
			close(ms->pipes_fds[u][0]);
			close(ms->pipes_fds[u][1]);
		}
		u++;
	}
	if (file_in(ms, (*ptr)) <= 0 || !file_out(ms, (*ptr))
		|| !ft_pre_args(ms, ptr))
		return (-1);
	if (ft_collect_info_line(ms, ptr, i) < 1)
		return (-1);
	if (ft_directions(ms) <= 0 || (ms->args[0] && !ft_exe(ms)))
		return (-1);
	return (1);
}

int	ft_organizer(t_mini *ms)
{
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	ft_start_pipe(ms, &ptr);
	while (ptr != NULL)
	{
		g_id = fork();
		if (g_id == 0)
		{
			signal(SIGQUIT, ft_ctrl);
			if (ft_in_fork(ms, &ptr, &i) < 0)
				return (-1);
			i = 0;
			ft_free_ms(ms);
			ft_free_fds(ms);
			ft_free_ms_envp(ms);
			ms->exit = 1;
			return (-1);
		}
		ft_next_pipe(ms, &ptr);
	}
	ft_close_all_fd(ms);
	ft_parent(ms);
	ft_clear_for_next_line(ms);
	return (1);
}

int	ft_pre_args(t_mini *ms, t_line **ptr)
{
	int		i;
	t_line	*original;

	i = 0;
	original = (*ptr);
	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		if ((*ptr)->type == 4 || (*ptr)->type == 3)
			i++;
		(*ptr) = (*ptr)->next;
	}
	if (ft_alloc_args(ms, i) < 0)
		return (-1);
	(*ptr) = original;
	return (1);
}

int	ft_alloc_args(t_mini *ms, int i)
{
	int	j;

	j = 0;
	ms->args = malloc(sizeof(char *) * (i + 1));
	if (ms->args == NULL)
		return (-1);
	while (j < i + 1)
	{
		ms->args[j] = NULL;
		j++;
	}
	return (1);
}

void	ft_clear_for_next_line(t_mini *ms)
{
	ft_free_fds(ms);
	ms->pipe_to_use = 0;
	ms->p_first = 1;
	ms->where_was_i = 0;
	dup2(ms->o_stdin, 0);
	dup2(ms->o_stdout, 1);
	ms->pipe = 0;
	ms->p_last = 0;
	ms->n_out_max = 0;
	ms->n_out_cur = 0;
	ms->n_in_cur = 0;
	ms->n_in_max = 0;
}
