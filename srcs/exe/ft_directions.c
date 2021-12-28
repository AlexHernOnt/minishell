/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 14:24:39 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 16:03:19 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		F T _ D I R E C T I O N S
*/

int	ft_directions(t_mini *ms)
{
	ft_input_source(ms);
	ft_pipes(ms);
	ms->pipe = 0;
	if (ms->red_out == 1 && ms->out_file != NULL)
	{
		if (ms->append)
			ms->fd_file_out = open(ms->out_file, O_CREAT | O_APPEND
					| O_RDWR, 0644);
		else
			ms->fd_file_out = open(ms->out_file, O_CREAT | O_TRUNC
					| O_RDWR, 0644);
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

void	ft_input_source(t_mini *ms)
{
	if (ms->in_cs)
	{
		ft_cs(ms);
		close(ms->pipe_cs[1]);
		dup2(ms->pipe_cs[0], 0);
	}
}

int	ft_cs(t_mini *ms)
{
	char	*aux;

	aux = NULL;
	while (abs_memcmp(aux, ms->in_file) != 1)
	{
		aux = readline("> ");
		if (abs_memcmp(aux, ms->in_file) == 1)
		{
			free(aux);
			return (0);
		}
		write(ms->pipe_cs[1], aux, ft_strlen(aux));
		write(ms->pipe_cs[1], "\0", 1);
		write(ms->pipe_cs[1], "\n", 1);
		free(aux);
	}
	return (0);
}

/*
**	Auxiliar funciton
*/

int	abs_memcmp(char *arr1, char *arr2)
{
	int		i;

	i = 0;
	if (!arr1 || !arr2)
		return (-1);
	while (arr1[i] != '\0' && arr2[i] != '\0' && arr1[i] == arr2[i] && i < 10)
		i++;
	if (arr1[i] == '\0' && arr2[i] == '\0')
		return (1);
	return (0);
}
