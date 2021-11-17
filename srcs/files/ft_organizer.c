/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:07 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/17 18:11:21 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/time.h>
/*
**		F T _ O R G A N I Z E R
*/

int	ft_organizer(t_mini *ms)
{
	t_line *ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	while (ptr != NULL)
	{
		if (!ft_pre_args(ms))
			return (-1);
		while (ms->pipe == 0 && ptr != NULL)
		{
			printf("Content: _%s_\t\t : Type %d\n", ptr->content, ptr->type);
			//free ptr->content_out
			if (ptr->type == 0)
				ms->in_file = ft_strdup(ptr->content);
			if (ptr->type == 1)
				ms->red_in = 1;
			if (ptr->type == 3 || ptr->type == 4)
				ms->args[i++] = ft_strdup(ptr->content);
			if (ptr->type == 5)
				ms->pipe = 1;
			if (ptr->type == 6)
				ms->red_out = 1;
			if (ptr->type == 8)
				ms->out_file = ft_strdup(ptr->content);
			ptr = ptr->next;
		}
		for (int a = 0; ms->args[a] != NULL;a++)
			printf("PENIS:   %s\n", ms->args[a]);
		usleep(2*1000*1000);
		if (!ft_directions(ms))
			return (0);
		if (ms->args[0] && !ft_exe(ms))
			return (0);
		ft_free_ms(ms);
	}
	return (1);
}

int	ft_pre_args(t_mini *ms)
{
	t_line	*ptr;
	int		i;

	i = 0;
	ptr = ms->list;
	if (ms->pos_list != NULL)
		ptr = ms->pos_list;
	while (ptr != NULL && ptr->type != 5) 
	{
		if (ptr->type == 4 || ptr->type == 3)
			i++;
		ptr = ptr->next;
	}
	if (ptr->type == 5)
		ms->pos_list = ptr->next;
	ms->args = malloc(sizeof(char *) * (i + 1));
	if (ms->args == NULL)
		return (-1);
	ms->args[i] = NULL;
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
