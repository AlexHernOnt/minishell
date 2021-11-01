/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:21:48 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/01 17:56:37 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_free_ms_envp(t_mini *ms)
{
	int i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		free(ms->envp[i]);
		i++;
	}
	free(ms->envp);
}

size_t	ft_strlen_dp(char **s)
{
	int		i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int		ft_check_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=' && ft_isascii(str[i]))
		i++;
	if (str[i] == '=' && i != 0)
			return (1);
	return (0);
}

//	HEY YOU!, listen, u only can pass this function individual strings, with no spaces,
//	split them and send them first 
//	pq "export AAA=1 BBB=2 CCC=3"

int	ft_export(t_mini *ms, char *aux)
{
	int		i;
	char	*str;
	char	**new_envp;

	i = 0;
	if (!ft_check_equal(aux + 7))
		return (-1);
	str = ft_strdup(aux + 7);
	new_envp = malloc(sizeof(char**) * ft_strlen_dp(ms->envp) + 2);
	if (!new_envp)
		return (-1);
	while (ms->envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(ms->envp[i]);
		i++;
	}
	ft_free_ms_envp(ms);
	new_envp[i] = str;
	new_envp[i + 1] = NULL;
	ms->envp = new_envp;
	return (1);
}
