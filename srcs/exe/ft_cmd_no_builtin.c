/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_no_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 13:41:16 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 14:15:25 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd_no_builtin(t_mini *ms)
{
	int		output;

	ms->args[0] = ft_path(ms->envp, ms->args);
	if (ms->args[0][0] && ms->args[0][0] != '.' &&
		ms->args[0][0] != '/')
	{
		ms->exit = 1;
		exit(ft_error(ms, 23, ms->args[0]));
	}
	output = execve(ms->args[0], ms->args, ms->envp);
	if (output == -1)
	{
		ft_free_ms(ms);
		ft_free_fds(ms);
		ft_free_ms_envp(ms);
		ms->exit = 1;
		exit(ft_error(ms, 23, ms->args[0]));
	}
	return (0);
}

void	ft_parent(t_mini *ms)
{
	int	output;
	int	pid;

	pid = 0;
	while (pid != -1)
	{
		pid = waitpid(-1, &output, 0);
		if (pid == g_id)
		{
			if (WIFSIGNALED(output) && WTERMSIG(output) == 2)
				ms->exit_status = 130;
			else if (WIFSIGNALED(output) && WTERMSIG(output) == 3)
			{
				printf("Quit: 3\n");
				ms->exit_status = 131;
			}
			else
				ms->exit_status = WEXITSTATUS(output);
		}
	}
}

int	ft_child(t_mini *ms, t_line *ptr, int i)
{
	if (ft_in_fork(ms, &ptr, &i) < 0)
		return (-1);
	i = 0;
	ft_free_ms(ms);
	ft_free_fds(ms);
	ms->exit = 1;
	return (-1);
}
