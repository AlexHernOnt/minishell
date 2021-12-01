/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:11:50 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/01 18:12:12 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_in(t_mini *ms)
{
	t_line	*ptr;
	int		fd;
	int		i;

	i = 0;
	ptr = ms->list;
	while (ptr != NULL)
	{
		if (ptr->type == 0)
			ms->n_in_max++;
		ptr = ptr->next;
	}
	ptr = ms->list;
	while (ptr != NULL && i < ms->n_in_max - 1)
	{
		if (ptr->type == 0)
		{
			fd = open(ptr->content, O_RDWR, 0777);
			if (fd == -1)
				return (ft_error(ms, 201, ptr->content));
			close(fd);
			i++;
		}
		ptr = ptr->next;
	}
	return (1);
}

int	file_out(t_mini *ms)
{
	t_line	*ptr;
	int		fd;
	int		i;

	i = 0;
	ptr = ms->list;
	while (ptr != NULL)
	{
		if (ptr->type == 8)
			ms->n_out_max++;
		ptr = ptr->next;
	}
	ptr = ms->list;
	while (ptr != NULL)
	{
		if (ptr->type == 8 && i < ms->n_out_max - 1)
		{
			fd = open(ptr->content, O_CREAT | O_TRUNC | O_RDWR, 0644);
			close(fd);
			i++;
		}
		ptr = ptr->next;
	}
	return (1);
}
