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
	ms->args = malloc(sizeof(char *) * (i + 1));
	ms->args[i] = NULL;
	if (ms->args == NULL)
		return (-1);
	return (1);
}

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
			ms->cmd = ft_strdup(ptr->content);
		if (ptr->type == 4)
			ms->args[i++] = ft_strdup(ptr->content);
		ptr = ptr->next;
	}

	ft_exe(ms);
	//free(ms->cmd);
	//free(ms->arg);
	return (1);
}

void	ft_displacer(t_mini *ms, char *cmd)
{
	char **new;



}

void	ft_cmd_no_built(t_mini *ms)
{
	char	*cmd;

	cmd = ft_path(ms->cmd, ms->envp);
	execve(cmd, ms->args, ms->envp);
}

int	ft_exe(t_mini *ms)
{
	if (ft_memcmp(ms->cmd, "echo", 4) == 0 && ms->cmd[4] == '\0')
		ft_echo(ms);
	else if (ft_memcmp(ms->cmd, "cd", 2) == 0 && ms->cmd[2] == '\0')
		ft_cd(ms);
	else if (ft_memcmp(ms->cmd, "pwd", 3) == 0 && ms->cmd[3] == '\0')
		ft_pwd();
	else if (ft_memcmp(ms->cmd, "env", 3) == 0 && ms->cmd[3] == '\0')
		ft_env(ms);
	else if (ft_memcmp(ms->cmd, "export", 6) == 0 && ms->cmd[6] == '\0')
		ft_export(ms, ms->cmd);
	else if (ft_memcmp(ms->cmd, "unset", 5) == 0 && ms->cmd[5] == '\0')
		ft_unset(ms, ms->cmd);
	else if (ft_memcmp(ms->cmd, "exit", 4) == 0 && ms->cmd[4] == '\0')
		return (0);
	else
	{
		ft_cmd_no_built(ms);
	}
//		if (ms->cmd[0] != '\0')
//			printf("-minishell: %s: Comand not found\n", ms->cmd);
	return (1);
}
