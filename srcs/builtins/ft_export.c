/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:21:48 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/22 18:12:21 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_dp(char **s)
{
	int		i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	ft_check_equal(char *str)
{
	int		i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	while (str[i] != '\0' && str[i] != '=' && ft_isascii(str[i]))
		i++;
	if (str[i] == '=' && i != 0)
		return (1);
	return (0);
}

//	HEY YOU!, listen
//	u only can pass this function individual strings, with no spaces,
//	split them and send them 1 by 1
//	pq "export AAA=1 BBB=2 CCC=3"

int	ft_export(t_mini *ms)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (ft_check_equal(ms->args[1]) == 0)
		return (ft_error(102, ms->args[1]));
	new_envp = malloc(sizeof(char **) * ft_strlen_dp(ms->envp) + 2);
	if (!new_envp)
		return (-1);
	while (ms->envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(ms->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(ms->args[1]);
	new_envp[i + 1] = NULL;
	ft_free_ms_envp(ms);
	ms->envp = new_envp;
	return (1);
}
