/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:07 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/21 18:21:17 by ahernand         ###   ########.fr       */
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
//			printf("Content: _%s_\t\t : Type %d, i = %d\n\n", ptr->content, ptr->type, i);
			if (ptr->type == 0)
				ms->in_file = ft_strdup(ptr->content);
			if (ptr->type == 1)
				ms->red_in = 1;
			if (ptr->type == 3 || ptr->type == 4)
			{
				ms->args[i] = ft_strdup(ptr->content);
				i++;
			}
			if (ptr->type == 5)
				ms->pipe = 1;
			if (ptr->type == 6)
				ms->red_out = 1;
			if (ptr->type == 8)
				ms->out_file = ft_strdup(ptr->content);
			ptr = ptr->next;
		}
		i = 0;
		if (!ft_directions(ms))
			return (0);
		if (ms->args[0] && !ft_exe(ms))
			return (0);
		ft_free_ms(ms);
	}
	ms->where_was_i = 0;
	return (1);
}

int	ft_pre_args(t_mini *ms)
{
	t_line	*ptr;
	int		i;

	ptr = ms->list;
	i = ms->where_was_i;
	while (i != 0 && ptr != NULL)
	{
		ptr = ptr->next;
		if (ptr->type == 4 || ptr->type == 3)
			i--;
	}
	i = 0;
	while (ptr != NULL && ptr->type != 5) 
	{
		if (ptr->type == 4 || ptr->type == 3)
			i++;
		ptr = ptr->next;
	}
	ms->args = malloc(sizeof(char *) * (i + 1));
	if (ms->args == NULL)
		return (-1);
	ms->args[i] = NULL;
	ms->where_was_i += i;
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
	ft_pipes(ms);
	ms->pipe = 0;
	return (1);
}

int	ft_pipes(t_mini *ms)
{
	if (ms->pipe == 1 && ms->red_out == 0 && ms->p_first == 1)
	{
		if (pipe(ms->pipe_fd_a) < 0)
			return (ft_error(150, NULL));
		dup2(ms->pipe_fd_a[1], 1);
		ms->p_last = 1;	
		ms->p_first = 0;
	}
	else if (ms->p_last == 1 && ms->pipe == 1)
	{
		if (pipe(ms->pipe_fd_b) < 0)
			return (ft_error(150, NULL));

		if (ms->p_using == 'a')
		{
			close(ms->pipe_fd_a[1]);
			dup2(ms->pipe_fd_a[0], 0);
			dup2(ms->pipe_fd_b[1], 1);
			ms->p_using = 'b';
		}
	}
	else if (ms->p_last == 1)
	{
		system("pwd > die_idiot");

		if (ms->p_using == 'b')
		{
			dup2(ms->pipe_fd_a[0], 0);
			close(ms->pipe_fd_a[1]);
		}
		if (ms->p_using == 'b')
		{
			close(ms->pipe_fd_a[0]);
			close(ms->pipe_fd_b[1]);
			dup2(ms->pipe_fd_b[0], 0);
		}
		dup2(ms->o_stdout, 1);
		ms->p_done = 1;
		ms->p_last = 0;
	}
	return (1);
}
