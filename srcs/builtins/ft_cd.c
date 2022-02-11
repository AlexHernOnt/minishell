/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:14 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/27 16:55:39 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*		OLD PWD AND PWD 	*/

void	ft_pre_cd(t_mini *ms)
{
	int		i;
	char	*str;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp("OLDPWD", ms->envp[i], 6) == 0 && ms->envp[i][6] == '=')
		{
			str = getcwd(NULL, 0);
			if (str)
			{
				free(ms->envp[i]);
				ms->envp[i] = ft_strjoin("OLDPWD=", str);
				free(str);
			}
		}
		i++;
	}
}

void	ft_post_cd(t_mini *ms)
{
	int		i;
	char	*str;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp("PWD", ms->envp[i], 3) == 0 && ms->envp[i][3] == '=')
		{
			str = getcwd(NULL, 0);
			if (str)
			{
				free(ms->envp[i]);
				ms->envp[i] = ft_strjoin("PWD=", str);
				free(str);
			}
		}
		i++;
	}
}

int	ft_cd(t_mini *ms)
{
	int		ret;

	ft_pre_cd(ms);
	ret = ft_cd_solo(ms, &ret);
	if (ret < 0)
		return (1);
	else if (!ret)
	{
		ft_post_cd(ms);
		return (0);
	}
	else
		ret = chdir(ms->args[1]);
	if (ret == -1)
	{
		ms->exit_status = 1;
		dup2(ms->o_stdout, 1);
		printf("-minishell: cd: %s: No such file or directory\n",
			ms->args[1]);
		return (1);
	}
	ft_post_cd(ms);
	return (0);
}

int	ft_cd_solo(t_mini *ms, int *ret)
{
	int		save;
	int		home_exist;

	home_exist = 0;
	ft_exist_doubt(ms, &home_exist, &save);
	if (ms->args[1] == NULL)
	{
		if (home_exist == 0)
		{
			printf("-minishell: cd: HOME not set\n");
			return (-1);
		}	
		else
		{
			(*ret) = chdir(ms->envp[save] + 5);
			return (0);
		}	
	}
	return (1);
}

void	ft_exist_doubt(t_mini *ms, int *home_exist, int *save)
{
	int		i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp("HOME", ms->envp[i], 4) == 0 && ms->envp[i][4] == '=')
		{
			(*save) = i;
			(*home_exist) = 1;
		}
		i++;
	}
}
