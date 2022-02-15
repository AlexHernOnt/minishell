/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:29:09 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 14:20:32 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		ft_exe
*/

int	ft_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/* Too long*/
int	ft_exe(t_mini *ms)
{
	if (ft_memcmp(ms->args[0], "echo", 4) == 0 && ms->args[0][4] == '\0')
		ms->exit_status = ft_echo(ms);
	else if (ft_memcmp(ms->args[0], "cd", 2) == 0 && ms->args[0][2] == '\0')
		ms->exit_status = ft_cd(ms);
	else if (ft_memcmp(ms->args[0], "pwd", 3) == 0 && ms->args[0][3] == '\0')
		ms->exit_status = ft_pwd();
	else if (ft_memcmp(ms->args[0], "env", 3) == 0 && ms->args[0][3] == '\0')
		ms->exit_status = ft_env(ms);
	else if (ft_memcmp(ms->args[0], "export", 6) == 0 && ms->args[0][6] == '\0')
		ms->exit_status = ft_export(ms);
	else if (ft_memcmp(ms->args[0], "unset", 5) == 0 && ms->args[0][5] == '\0')
		ms->exit_status = ft_unset(ms);
	else if (ft_memcmp(ms->args[0], "exit", 4) == 0 && ms->args[0][4] == '\0')
		return (ft_exe_exit(ms));
	else
	{
		ft_cmd_no_builtin(ms);
		if (ms->exit_status == 127)
		{
			ft_fd_clean(ms);
			return (0);
		}
	}
	ft_fd_clean(ms);
	return (1);
}

int	ft_exe_exit(t_mini *ms)
{
	printf("exit\n");
	if (!ms->args[1] || !ft_numeric(ms->args[1])
		|| (ms->args[1] && !ms->args[2]))
	{
		ms->exit = 1;
		if (ms->args[1] && ft_numeric(ms->args[1]))
			ms->exit_status = ft_atoi(ms->args[1]);
		else if (ms->args[1])
			ms->exit_status = ft_error(ms, 255, ms->args[1]);
	}
	else
		ms->exit_status = ft_error(ms, 1, "exit");
	return (0);
}

void	ft_fd_clean(t_mini *ms)
{
	ft_redir_clean(ms);
	if (ms->p_done == 1)
	{
		dup2(ms->o_stdin, 0);
		ms->p_first = 1;
		ms->p_done = 0;
	}
	if (ms->in_cs)
	{
		close(ms->pipe_cs[0]);
		if (ms->in_file)
			free(ms->in_file);
		ms->in_file = NULL;
		ms->in_cs = 0;
	}
}

void	ft_redir_clean(t_mini *ms)
{
	if (ms->red_out == 1)
	{
		close(ms->fd_file_out);
		if (ms->out_file)
			free(ms->out_file);
		ms->out_file = NULL;
		dup2(ms->o_stdout, 1);
		ms->red_out = 0;
	}
	if (ms->red_in == 1)
	{
		close(ms->fd_file_in);
		if (ms->in_file)
			free(ms->in_file);
		ms->out_file = NULL;
		dup2(ms->o_stdin, 0);
		ms->red_in = 0;
	}
}
