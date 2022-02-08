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

void ft_start_pipe(t_mini *ms, t_line **ptr)
{
	int		i;
	t_line	*original;

	i = 0;
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

void ft_next_pipe(t_mini *ms, t_line **ptr)
{
	int		i;
	t_line	*save;

	i = 0;
 	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		(*ptr) = (*ptr)->next;
	}
	if ((*ptr) != NULL && (*ptr)->type == 5)
		(*ptr) = (*ptr)->next;
	save = (*ptr);
	while ((*ptr) != NULL && (*ptr)->type != 5)
	{
		(*ptr) = (*ptr)->next;
	}
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
	(*ptr) = save;
}

int	ft_organizer(t_mini *ms)
{
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	g_id = 101;
	ft_start_pipe(ms, &ptr);
	if (pipe(ms->pipe_fd_a) < 0)
		return (ft_error(ms, 150, NULL));
	while (ptr != NULL)
	{
		g_id = fork();
		if (g_id == 0)
		{
		//	printf("pipe: %d\np_last: %d\n", ms->pipe, ms->p_last);
			if (file_in(ms, ptr) <= 0 || !file_out(ms, ptr) || !ft_pre_args(ms, &ptr))
				return (-1);
			if (ft_collect_info_line(ms, &ptr, &i) < 1)
				return (-1);
			i = 0;
			if (ft_directions(ms) <= 0 || (ms->args[0] && !ft_exe(ms)))
				return (-1);

			//ft_free_ms(ms);
			ms->exit = 1;
			return (-1);
		}
		ft_next_pipe(ms, &ptr);
	}
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
	ms->p_first = 1;
	ms->where_was_i = 0;
	ms->p_using = 'a';
	ms->p_b_exists = 0;
	dup2(ms->o_stdin, 0);
	dup2(ms->o_stdout, 1);
	ms->pipe = 0;
	ms->p_last = 0;
	ms->n_out_max = 0;
	ms->n_out_cur = 0;
	ms->n_in_cur = 0;
	ms->n_in_max = 0;
}
