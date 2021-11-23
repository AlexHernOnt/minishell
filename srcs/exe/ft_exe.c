/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:29:09 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/22 15:08:32 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ft_export(ms);
	else if (ft_memcmp(ms->args[0], "unset", 5) == 0 && ms->args[0][5] == '\0')
		ft_unset(ms);
	else if (ft_memcmp(ms->args[0], "exit", 4) == 0 && ms->args[0][4] == '\0')
		return (0);
	else
		ft_cmd_no_built(ms);
	ft_fd_clean(ms);
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

//		for (int j = 0; ms->args[j] != NULL ;j++)
//			printf("_Period: _%s_ && %d\n", ms->args[j], j);

		output = execve(ms->args[0], ms->args, ms->envp);
		//free ms vars
		if (output == -1)
			printf("-minishell: %s: Comand not found\n", ms->args[0]);
	}
	else if (id != 0)
		wait(NULL);
}

void ft_fd_clean(t_mini *ms)
{
	if (ms->red_out == 1)
	{
		close(ms->fd_file_out);
		free(ms->out_file);
		ms->out_file = NULL;
		dup2(ms->o_stdout, 1);
		ms->red_out = 0;
	}
	if (ms->red_in == 1)
	{
		close(ms->fd_file_in);
		free(ms->in_file);
		ms->out_file = NULL;
		dup2(ms->o_stdin, 0);
		ms->red_in = 0;
	}
	else if (ms->p_done == 1)
	{
		dup2(ms->o_stdin, 0);
		if (ms->p_using == 'a')
			close(ms->pipe_fd_a[0]);
		else if (ms->p_using == 'b')
			close(ms->pipe_fd_b[0]);
		ms->p_first = 1;
		ms->p_done = 0;
	}
}
