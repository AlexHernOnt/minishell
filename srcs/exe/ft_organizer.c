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

int	ft_organizer(t_mini *ms)
{
	t_line	*ptr;
	int		i;
	int		lock;

	i = 0;
	lock = 0;
	ptr = ms->list;
	while (ptr != NULL && !lock)
	{
		if (!ft_pre_args(ms) || file_in(ms, ptr) <= 0 || !file_out(ms, ptr))
			return (-1);
		if (ft_collect_info_line(ms, &ptr, &i) < 1)
			return (-1);
		i = 0;
		if (ft_directions(ms) <= 0)
			lock = 1;
		if (lock == 0 && ms->args[0] && !ft_exe(ms))
			lock = 1;
		ft_free_ms(ms);
		ft_fd_clean(ms);
		ft_clear_next_segment(ms);
	}
	ft_clear_for_next_line(ms);
	return (1);
}

int	ft_pre_args(t_mini *ms)
{
	t_line	*ptr;
	int		i;
	int		n_p;

	i = 0;
	n_p = 0;
	ptr = ms->list;
	while (ptr != NULL && n_p != ms->where_was_i)
	{
		if (ptr->type == 5)
			n_p++;
		ptr = ptr->next;
	}
	ms->where_was_i++;
	while (ptr != NULL && ptr->type != 5)
	{
		if (ptr->type == 4 || ptr->type == 3)
			i++;
		ptr = ptr->next;
	}
	if (ft_alloc_args(ms, i) < 0)
		return (-1);
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

void	ft_clear_next_segment(t_mini *ms)
{
	ms->n_out_max = 0;
	ms->n_out_cur = 0;
	ms->n_in_max = 0;
	ms->n_in_cur = 0;
	ms->n_in_max = 0;
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
}
