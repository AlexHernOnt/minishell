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

	g_id = fork();
	if (g_id == 0)
	{
		signal(SIGQUIT, ft_ctrl);
		ms->args[0] = ft_path(ms->envp, ms->args);
		if (ms->args[0][0] && ms->args[0][0] != '.' &&
			ms->args[0][0] != '/')
		{
			ms->exit = 1;
			return (ft_error(ms, 23, ms->args[0]));
		}
		output = execve(ms->args[0], ms->args, ms->envp);
		if (output == -1)
		{
			dup2(2, 1);
			printf("-minishell: %s: Comand not found\n", ms->args[0]);
			dup2(ms->o_stdout, 1);
			ms->exit = 1;
		}
	}
	else if (g_id != 0)
		ft_parent(ms, &output);
	return (0);
}

void	ft_parent(t_mini *ms, int *output)
{
	waitpid(-1, output, 0);
	if (WIFSIGNALED(output) && WTERMSIG(output) == 2)
		ms->exit_status = 130;
	else if (WIFSIGNALED(output) && WTERMSIG(output) == 3)
	{
		ms->exit_status = 131;
		printf("Quit: 3\n");
	}
	else
		ms->exit_status = WEXITSTATUS(output);
}
