/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_hub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:28:43 by ahernand          #+#    #+#             */
/*   Updated: 2022/02/11 15:28:44 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_built_in(t_mini *ms)
{
	t_line	*lst;

	lst = ms->list;
	while (lst != NULL && lst->type != 3)
	{
		lst = lst->next;
	}
	if (lst != NULL && lst->type == 3)
	{
		if ((ft_memcmp(lst->content, "echo", 4) == 0 && lst->content[4] == '\0')
			|| (ft_memcmp(lst->content, "cd", 2) == 0 && lst->content[2] == '\0')
			|| (ft_memcmp(lst->content, "pwd", 3) == 0 && lst->content[3] == '\0')
			|| (ft_memcmp(lst->content, "env", 3) == 0 && lst->content[3] == '\0')
			|| (ft_memcmp(lst->content, "export", 6) == 0 && lst->content[6] == '\0')
			|| (ft_memcmp(lst->content, "unset", 5) == 0 && lst->content[5] == '\0')
			|| (ft_memcmp(lst->content, "exit", 4) == 0 && lst->content[4] == '\0'))
			return(1);
		else
			return (0);
	}
	return (0);
}

int	ft_single_cmd(t_mini *ms)
{
	t_line	*lst;
	t_line	*og;

	lst = ms->list;
	og = ms->list;
	while (lst != NULL && lst->type != 5)
	{
		lst = lst->next;
	}
	if (lst != NULL && lst->type == 5)
	{
		ms->list = og;
		return (1);
	}
	ms->list = og;
	return (0);
}

int	ft_exe_2(t_mini *ms)
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
		ft_env_pwd(ms);
		ft_fd_clean(ms);
		return (-1);
	}
	ft_env_pwd(ms);
	ft_fd_clean(ms);
	return (1);
}

int	builtins_hub(t_mini *ms, int i, int lock)
{
	t_line	*ptr;

	ptr = ms->list;
	while (ptr != NULL && !lock)
	{
		if (file_in(ms, ptr) <= 0 || !file_out(ms, ptr)
			|| !ft_pre_args(ms, &ms->list))
			return (-1);
		if (ft_collect_info_line(ms, &ptr, &i) < 1)
			return (-1);
		i = 0;
		if (ft_directions(ms) <= 0)
			lock = 1;
		if (lock == 0 && ms->args[0] && ft_exe_2(ms) < 0)
		{
			lock = 1;
			ft_free_ms(ms);
			ft_clear_for_next_line(ms);
			return (-1);
		}
		ft_free_ms(ms);
	}
	ft_clear_for_next_line(ms);
	return (1);
}
