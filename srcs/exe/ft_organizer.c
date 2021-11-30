/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_organizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:13:07 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/30 19:19:29 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		F T _ O R G A N I Z E R
*/

int 	ft_newfile(char *ptr, int append)
{
	int		fd;

	if (append == 1)
		fd = open(ptr, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		fd = open(ptr, O_CREAT | O_TRUNC | O_RDWR, 0644);
	close(fd);
	return (0);
}

int	ft_organizer(t_mini *ms)
{
	t_line *ptr;
	int		i;
	int		lock;

	i = 0;
	lock = 0;
	ptr = ms->list;
	while (ptr != NULL && !lock)
	{
		if (!ft_pre_args(ms))
			return (-1);
		while (ms->pipe == 0 && ptr != NULL)
		{
//			printf("Content: _%s_\t\t : Type %d, i = %d\n\n", ptr->content, ptr->type, i);
			if (ptr->type == 0)
			{
				if (ms->in_file != NULL)
					ft_newfile(ptr->content);
				else
					ms->in_file = ft_strdup(ptr->content);
			}
			if (ptr->type == 1)
				ms->red_in = 1;
			if (ptr->type == 7)
				ms->append = 1;
			if (ptr->type == 3 || ptr->type == 4)
			{
				ms->args[i] = ft_strdup(ptr->content);
				i++;
			}
			if (ptr->type == 5)
				ms->pipe = 1;
			if (ptr->type == 6 || ptr->type == 7)
				ms->red_out = 1;
			if (ptr->type == 8)
			{
				if (ms->out_file != NULL)
				{
					if (ft_newfile(ptr->content, 0))
						return (-1);
				}
				else
					ms->out_file = ft_strdup(ptr->content);
			}
			ptr = ptr->next;
		}
		i = 0;
		if (ft_directions(ms) <= 0)
			lock = 1;
		if (lock == 0 && ms->args[0] && !ft_exe(ms))
			lock = 1;
		ft_free_ms(ms);
		ft_fd_clean(ms);
	}
	ms->p_first = 1;
	ms->where_was_i = 0;
	ms->p_using = 'a';
	ms->p_b_exists = 0;
	dup2(ms->o_stdin, 0);
	dup2(ms->o_stdout, 1);
	ms->pipe = 0;
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
	ft_pipes(ms);
	ms->pipe = 0;
	if (ms->red_out == 1 && ms->out_file != NULL)
	{
		if (ms->append)
			ms->fd_file_out = open(ms->out_file, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			ms->fd_file_out = open(ms->out_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (ms->fd_file_out < 0)
			return (0);
		dup2(ms->fd_file_out, 1);
	}
	if (ms->red_in == 1 && ms->in_file != NULL)
	{
		ms->fd_file_in = open(ms->in_file, O_RDWR, 0777);
		if (ms->fd_file_in < 0)
		{
			return (ft_error(ms, 201, ms->in_file));
		}
		dup2(ms->fd_file_in, 0);
	}
	return (1);
}


int	ft_pipes(t_mini *ms)
{
	if (ms->pipe == 1 && ms->p_first == 1)
	{
		if (pipe(ms->pipe_fd_a) < 0)
			return (ft_error(ms, 150, NULL));
		dup2(ms->pipe_fd_a[1], 1);
		ms->p_last = 1;	
		ms->p_first = 0;
	}
	else if (ms->p_last == 1 && ms->pipe == 1)
	{
		if (ms->p_using == 'a')
		{
			close(ms->pipe_fd_a[1]);
			dup2(ms->pipe_fd_a[0], 0);

			if (pipe(ms->pipe_fd_b) < 0)
				return (ft_error(ms, 150, NULL));
			ms->p_b_exists = 1;

			dup2(ms->pipe_fd_b[1], 1);
			ms->p_using = 'b';
		}
		else if (ms->p_using == 'b')
		{
			close(ms->pipe_fd_b[1]);
			close(ms->pipe_fd_a[0]);
			dup2(ms->pipe_fd_b[0], 0);

			if (pipe(ms->pipe_fd_a) < 0)
				return (ft_error(ms, 150, NULL));

			dup2(ms->pipe_fd_a[1], 1);
			ms->p_using = 'a';
		}
	}
	else if (ms->p_last == 1)
	{
		if (ms->p_using == 'a')
		{
			close(ms->pipe_fd_a[1]);
			if (ms->p_b_exists == 1)
				close(ms->pipe_fd_b[0]);

			dup2(ms->pipe_fd_a[0], 0);
			dup2(ms->o_stdout, 1);
		}
		else if (ms->p_using == 'b')
		{
			close(ms->pipe_fd_a[0]);
			if (ms->p_b_exists == 1)
				close(ms->pipe_fd_b[1]);

			dup2(ms->pipe_fd_b[0], 0);
			dup2(ms->o_stdout, 1);
		}
		ms->p_done = 1;
		ms->p_last = 0;
	}
	return (1);
}
