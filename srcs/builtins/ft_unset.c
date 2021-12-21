/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:56:27 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/29 13:54:22 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_alpha_arr(char *str)
{
	int		i;

	i = 0;
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (-1);
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (-1);
		i++;
	}
	return (1);
}

void	ft_delete(t_mini *ms, int here)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen_dp(ms->envp)));
	if (new_envp != NULL)
	{
		while (i != here)
		{
			new_envp[i] = ft_strdup(ms->envp[i]);
			i++;
		}
		while (ms->envp[i + 1] != NULL)
		{
			new_envp[i] = ft_strdup(ms->envp[i + 1]);
			i++;
		}
		new_envp[i] = NULL;
		ft_free_ms_envp(ms);
		ms->envp = new_envp;
	}
}

int	ft_pos_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	return (i);
}

int	ft_unset(t_mini *ms)
{
	int	j;

	j = 1;
	while (ms->args[j])
	{
		if (ft_doer_unset(ms, j) <= 0)
			return (1);
		j++;
	}
	return (0);
}

int ft_doer_unset(t_mini *ms, int j)
{
	int		i;
	char	*cut;

	i = -1;
	if (ft_alpha_arr(ms->args[j]) == -1)
		return (ft_error(ms, 101, ms->args[j]));
	while (ms->envp[++i] != NULL)
	{
		cut = ft_strdup(ms->envp[i]);
		cut[ft_pos_equal(ms->envp[i])] = '\0';
		if (ft_memcmp(cut, ms->args[j], ft_strlen(ms->args[j])) == 0)// && cut[ft_strlen(ms->args[1])] == '\0')
		{
			ft_delete(ms, i);
			free(cut);
			return (1);
		}
		free(cut);
	}
	return (0);
}
