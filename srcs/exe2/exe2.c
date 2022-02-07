/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 10:57:59 by amorion-          #+#    #+#             */
/*   Updated: 2022/02/06 10:58:01 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int number_cmd(t_line *line)
{
	t_line  *ptr;
	int		c;

	ptr = line;
	c = 0;
	while(ptr)
	{
		if (ptr->type == 3)
			c++;
		ptr = ptr->next;
	}
	return(c);
}

void	pipe_generator(int *inpipe, int *outpipe, int i, int nc)
{
	if (i == 1 && i > nc) // primer comando: solo pipe se dalida
		inpipe[0] = STDIN_FILENO;
		pipe(outpipe);
	if (i < nc && i != 1) // comando intermedio entra el pipe del anterior y sale nuevo pipe
	{
		inpipe = outpipe;
		pipe(outpipe);
	}
	if (i == nc && i > 1) // último comando de varios: solo entrada
	{
		inpipe = outpipe;
		outpipe[1] = STDOUT_FILENO;
	}
	if (i == 1 && i == nc) // Proceso único redirige a entrada y salida directamente
	{
		inpipe[0] = STDIN_FILENO;
		outpipe[1] = STDOUT_FILENO;
	}
}

int	infile(t_line *list, t_mini *ms) //  Añadir cs
{
	t_line *ptr;

	ptr = list;
	while(ptr)
	{
		if (ptr->type == 1)
		{
			if (ms->fd_file_in)
				close(ms->fd_file_in);
			if (ms->pipe_cs[0])
				close(ms->pipe_cs[0]);
			ms->fd_file_in = open(ptr->content, O_RDONLY);
			if(ms->fd_file_in == -1)
			{
				perror(ptr->content);
				return(1);
			}
		}
		if (ptr->type == 2) //???????? << check original
		{
			ms->in_file = ptr->next->content;
			pipe(ms->pipe_cs);
			ft_cs(ms);
			close(ms->pipe_cs[1]);
			dup2(ms->pipe_cs[0], ms->fd_file_in);
		}
		ptr = ptr->next;
	}
	return(0);
}

int outfile(t_line *list, t_mini *ms)
{
	t_line *ptr;

	ptr = list;
	while(ptr)
	{
		if (ptr->type == 6 || ptr->type == 7)
		{
			if (ms->fd_file_out)
				close(ms->fd_file_out);
			if (ptr->type == 6)
				ms->fd_file_out = open(ptr->next->content, O_WRONLY, O_CREAT, O_TRUNC);
			if (ptr->type == 7)
				ms->fd_file_out = open(ptr->next->content, O_WRONLY, O_CREAT, O_APPEND);
			if (ms->fd_file_out == -1)
			{
				perror(ptr->next->content);
				return (1);
			}
		}
		ptr = ptr->next;
	}
	return (0);
}
char	**ft_get_args(t_line *initial)
{
	t_line	*ptr;
	int		size;
	int		i;
	char	**args;

	ptr = initial;
	size = 0;
	i = 0;
	while(ptr && (ptr->type == 3 || ptr->type == 4))
		size++;
	args = malloc(size + 1);
	ptr = initial;
	while(i < size)
	{
		args[i] = ptr->content;
		i++;
	}
	args[i] = 0;
	return(args);

}

int	ft_comand_exe(int current, t_mini *ms)
{
	t_line *ptr;

	ptr = ms->list;
	while(current > 1) // llega al comando i
	{
		if (ptr->type == 5)
			current--;
		ptr = ptr->next;
	}
	if (infile(ptr, ms) || outfile(ptr, ms))
		exit(-1);
	if (ms->fd_file_in > 0)
		dup2(ms->fd_file_in, STDIN_FILENO);
	if (ms->fd_file_out > 0)
		dup2(ms->fd_file_out, STDOUT_FILENO);
	return(0);
}



void ft_exe2(t_mini *ms)
{
	int nc;
	int i;
	int inpipe[2];
	int outpipe[2];
	
	nc = number_cmd(ms->list);
	i = 1;
	while(i <= nc)
	{
		pipe_generator(inpipe, outpipe, i, nc); // No estoy seguro de que esto funcione
		g_id = fork();
		if (!g_id)
		{
			// Redirecciones
			// Ejecutar comandos
		}
		i++;
	}
	if (g_id)
		ft_parent(ms);
	g_id = -1;
}