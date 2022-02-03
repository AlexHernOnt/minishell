/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:53:50 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/02 17:38:36 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_mini *ms)
{
	int		i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		printf("%s\n", ms->envp[i]);
		i++;
	}
	return (0);
}

char	**ft_strdup_envp(char **envp)
{
	char	**new_envp;
	int		i;
	int		num;
	char	*aux;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen_dp(envp) + 1));
	if (new_envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_memcmp("SHLVL", envp[i], 5) == 0 && envp[i][5] == '=')
		{
			num = ft_atoi(envp[i] + 6);
			aux = ft_itoa(num + 1);
			new_envp[i] = ft_strjoin("SHLVL=", aux);
			if (aux)
				free(aux);
		}
		else
			new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_env_pwd(t_mini *ms)
{
	char	*str;
	int		i;

	i = 0;
	str = getcwd(NULL, 0);
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp("PWD", ms->envp[i], 4) == 0 && ms->envp[i][3] == '=')
		{
			free(ms->envp[i]);
			ms->envp[i] = ft_strjoin("PWD=", str);
		}
		i++;
	}
	free(str);
}