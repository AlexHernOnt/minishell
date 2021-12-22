/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:14 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/22 18:30:38 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_mini *ms)
{
    int     i;
	int		ret;

	i = 0;
	if (ms->args[1] == NULL || ft_only_spaces(ms->args[1]))
	{
    	while (ms->envp[i] != NULL)
		{
        	if (ft_memcmp("HOME", ms->envp[i], 4) == 0
                && ms->envp[i][4] == '=')
			{
				chdir(ms->envp[i] + 5);
			}
    	    i++;
		}
	}
	ret = chdir(ms->args[1]);
	if (ret == -1)
	{
		ms->exit_status = 1;
		printf("-minishell: cd: %s: No such file or directory\n", ms->args[1]);
		return (1);
	}
	return (0);
}
