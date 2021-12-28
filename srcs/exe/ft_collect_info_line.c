/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collect_info_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:30:02 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 16:35:20 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		ft_collect_info_line
*/

int	ft_collect_info_line(t_mini *ms, t_line **ptr, int *i)
{
	while (ms->pipe == 0 && *ptr != NULL)
	{
		if ((*ptr)->type == 0)
			ft_num_of_infiles(ms, ptr);
		if ((*ptr)->type == 1 && ft_collect_cs(ms) != 1)
			return (-1);
		if ((*ptr)->type == 7)
			ms->append = 1;
		if ((*ptr)->type == 3 || (*ptr)->type == 4)
		{
			ms->args[(*i)] = ft_strdup((*ptr)->content);
			*i = *i + 1;
		}
		if ((*ptr)->type == 5)
			ms->pipe = 1;
		if ((*ptr)->type == 6 || (*ptr)->type == 7)
			ms->red_out = 1;
		if ((*ptr)->type == 8)
			ft_num_of_outfiles(ms, ptr);
		(*ptr) = (*ptr)->next;
	}
	return (1);
}

void	ft_num_of_infiles(t_mini *ms, t_line **ptr)
{
	ms->n_in_cur++;
	if (ms->n_in_cur == ms->n_in_max)
	{
		ms->in_file = ft_strdup((*ptr)->content);
	}
}

int	ft_collect_cs(t_mini *ms)
{
	ms->in_cs = 1;
	if (pipe(ms->pipe_cs) < 0)
		return (ft_error(ms, 150, NULL));
	return (1);
}

void	ft_num_of_outfiles(t_mini *ms, t_line **ptr)
{
	ms->n_out_cur++;
	if (ms->n_out_cur == ms->n_out_max)
		ms->out_file = ft_strdup((*ptr)->content);
}
