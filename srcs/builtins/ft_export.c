/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:21:48 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/27 17:09:47 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export(t_mini *ms)
{
	int		j;

	j = 1;
	while (ms->args[j] != NULL)
	{
		if (ft_alredy_exists(ms, j))
			ft_delete(ms, ms->export_pos);
		if (ft_doer_export(ms, j) <= 0)
			return (1);
		j++;
	}
	return (0);
}

int	ft_doer_export(t_mini *ms, int j)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (ft_check_equal(ms->args[j]) == 0)
		return (ft_error(ms, 102, ms->args[j]));
	new_envp = malloc(sizeof(char **) * (ft_strlen_dp(ms->envp) + 2));
	if (!new_envp)
		return (-1);
	while (ms->envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(ms->envp[i]);
		i++;
	}
	ft_no_quotes(ms, j, '\'');
	ft_no_quotes(ms, j, '"');
	new_envp[i] = ft_strdup(ms->args[j]);
	new_envp[i + 1] = NULL;
	ft_free_ms_envp(ms);
	ms->envp = new_envp;
	return (1);
}

/*
**	Exception
*/

int	ft_alredy_exists(t_mini *ms, int j)
{
	int		i;

	i = 0;
	while (ms->envp[i] != '\0')
	{
		if (ft_memcmp(ms->envp[i], ms->args[j], ft_pos_equal(ms->envp[i])) == 0
			&& ms->args[j][ft_pos_equal(ms->envp[i])]
			&& ms->args[j][ft_pos_equal(ms->envp[i])] == '=')
		{
			ms->export_pos = i;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
**	Utils for this
*/

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
	while (str[i] != '\0' && str[i] != '=' && (ft_isalnum(str[i])
			|| str[i] == '_'))
		i++;
	if (str[i] == '=' && i != 0)
		return (1);
	return (0);
}
