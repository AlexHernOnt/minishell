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
void	ft_input_vars(t_mini *ms, t_line **ptr)
{
	if ((*ptr)->type == 7)
		ms->append = 1;
	else
		ms->append = 0;
	ms->red_out = 1;
}

int	ft_collect_info_line(t_mini *ms, t_line **ptr, int *i)
{
	while (*ptr != NULL && (*ptr)->type != 5)
	{
//		if ((*ptr)->type == 1)
//			ft_num_of_infiles(ms, ptr);
//		if ((*ptr)->type == 2 && ft_collect_cs(ms, ptr) != 1)
//			return (-1);
		if ((*ptr)->type == 3 || (*ptr)->type == 4)
		{
			ms->args[(*i)] = ft_strdup((*ptr)->content);
			*i = *i + 1;
		}
//		if ((*ptr)->type == 6 || (*ptr)->type == 7)
//			ft_input_vars(ms, ptr);
//		if ((*ptr)->type == 8)
//			ft_num_of_outfiles(ms, ptr);
		(*ptr) = (*ptr)->next;
	}
	return (1);
}

void	ft_num_of_infiles(t_mini *ms, t_line **ptr)
{
	ms->n_in_cur++;
	if (ms->n_in_cur == ms->n_in_max)
	{
		ms->in_file = ft_strdup((*ptr)->next->content);
		ms->red_in = 1;
	}
}

int	ft_collect_cs(t_mini *ms, t_line **ptr)
{
	ms->in_cs = 1;
	ms->in_file = ft_strdup((*ptr)->next->content);
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
