/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:07 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/17 13:13:14 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		F T _ O R G A N I Z E R
*/

int	ft_organizer(t_mini *ms)
{
	t_line *ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	if (!ft_pre_args(ms))
		return (-1);
	while (ptr != NULL)
	{
		//free ptr->content_out
		if (ptr->type == 0)
			ms->in_file = ft_strdup(ptr->content);
		if (ptr->type == 1)
			ms->red_in = 1;
		if (ptr->type == 3 || ptr->type == 4)
			ms->args[i++] = ft_strdup(ptr->content);
		if (ptr->type == 5)
		{
			ms->pipe = 1;
			continue ;
		}
		if (ptr->type == 7)
			ms->red_out = 1;
		if (ptr->type == 8)
			ms->out_file = ft_strdup(ptr->content);
		ptr = ptr->next;
	}
	if (!ft_directions(ms))
		return (0);
	if (ms->args[0] && !ft_exe(ms))
		return (0);
	ft_free_ms(ms);
	return (1);
}

int	ft_pre_args(t_mini *ms)
{
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	while (ptr != NULL)
	{
		if (ptr->type == 4)
			i++;
		ptr = ptr->next;
	}
	ms->args = malloc(sizeof(char *) * (i + 2));
	if (ms->args == NULL)
		return (-1);
	ms->args[i + 1] = NULL;
	return (1);
}

/*
**		F T _ D I R E C T I O N S
*/

int	ft_directions(t_mini *ms)
{
	if (ms->red_out == 1)
	{
		ms->fd_file_out = open(ms->out_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (ms->fd_file_out < 0)
			return (-1);
		dup2(ms->fd_file_out, 1);
	}
	if (ms->red_in == 1)
	{
		ms->fd_file_in = open(ms->in_file, O_RDWR, 0777);
		if (ms->fd_file_in < 0)
			return (ft_error(201, ms->in_file));
		dup2(ms->fd_file_in, 0);
	}
	if (ms->pipe == 1 && ms->red_out == 0)
	{
		if (pipe(ms->pipe_fd) < 0)
			return (ft_error(150, NULL));
		dup2(ms->pipe_fd[1], 1);
	}
	return (1);
}
