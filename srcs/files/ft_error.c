/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:30:24 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/23 13:05:29 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_leaks(void)
{
	system("leaks minishell");
}

int	ft_error(int code, char *arg)
{
	if (code == 101)
		printf("-minishell: unset: `%s': not a valid identifier\n", arg);
	if (code == 102)
		printf("-minishell: export: `%s': not a valid identifier\n", arg);
	if (code == 105)
		printf("Pipe failed\n");
	if (code == 201)
		printf("-minishell: %s: No such file or directory\n", arg);
	return (-1);
}

void	ft_free_ms(t_mini *ms)
{
	int	i;

	i = 0;
	while (ms->args[i] != NULL)
	{
		if (ms->args[i])
		{
			free(ms->args[i]);
			ms->args[i] = NULL;
		}
		i++;
	}
	free(ms->args);
	ms->args = NULL;
}

void	ft_free_ms_envp(t_mini *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
//		printf("_%s_\n", ms->envp[i]);
		free(ms->envp[i]);
		ms->envp[i] = NULL;
		i++;
	}
	free(ms->envp);
	ms->envp = NULL;
}

