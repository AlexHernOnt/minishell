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
		output = ft_error(ms, 23, ms->args[0]);
		exit(output);
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

void	ft_clear_for_next_line(t_mini *ms)
{
	ft_free_fds(ms);
	ms->pipe_to_use = 0;
	ms->p_first = 1;
	ms->where_was_i = 0;
	dup2(ms->o_stdin, 0);
	dup2(ms->o_stdout, 1);
	ms->pipe = 0;
	ms->p_last = 0;
	ms->n_out_max = 0;
	ms->n_out_cur = 0;
	ms->n_in_cur = 0;
	ms->n_in_max = 0;
}
