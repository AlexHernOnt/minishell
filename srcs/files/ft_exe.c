/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:37:12 by ahernand          #+#    #+#             */
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
		if (ptr->type == 3)
			ms->args[i++] = ft_strdup(ptr->content);
		if (ptr->type == 4)
			ms->args[i++] = ft_strdup(ptr->content);
		if (ptr->type == 7)
			ms->red_out = 1;
		if (ptr->type == 8)
			ms->out_file = ft_strdup(ptr->content);
		ptr = ptr->next;
	}
	ft_directions(ms);
	if (ms->args[0] && !ft_exe(ms))
		return (0);
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
	return (1);
}

/*
**		F T _ E X E 
*/

int	ft_exe(t_mini *ms)
{
	if (ft_memcmp(ms->args[0], "echo", 4) == 0 && ms->args[0][4] == '\0')
		ft_echo(ms);
	else if (ft_memcmp(ms->args[0], "cd", 2) == 0 && ms->args[0][2] == '\0')
		ft_cd(ms);
	else if (ft_memcmp(ms->args[0], "pwd", 3) == 0 && ms->args[0][3] == '\0')
		ft_pwd();
	else if (ft_memcmp(ms->args[0], "env", 3) == 0 && ms->args[0][3] == '\0')
		ft_env(ms);
	else if (ft_memcmp(ms->args[0], "export", 6) == 0 && ms->args[0][6] == '\0')
		ft_export(ms, ms->args[0]);
	else if (ft_memcmp(ms->args[0], "unset", 5) == 0 && ms->args[0][5] == '\0')
		ft_unset(ms, ms->args[0]);
	else if (ft_memcmp(ms->args[0], "exit", 4) == 0 && ms->args[0][4] == '\0')
		return (0);
	else
		ft_cmd_no_built(ms);
	return (1);
}

void	ft_cmd_no_built(t_mini *ms)
{
	int		id;
	int		output;

	id = fork();
	if (id == 0)
	{
		ms->args[0] = ft_path(ms->envp, ms->args);
		output = execve(ms->args[0], ms->args, ms->envp);
		//free shit!
		if (output == -1)
			printf("-minishell: %s: Comand not found\n", ms->args[0]);
	}
	else if (id != 0)
	{
		wait(NULL);
		if (ms->red_out == 1)
		{
			close(ms->fd_file_out);
			dup2(ms->o_stdin, 1);
			ms->red_out = 0;
		}
	}
}
