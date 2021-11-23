/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:56:27 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/23 13:15:14 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	HEY YOU!, listen, u only can pass this function 
//	individual strings, with no spaces, split them and send them first
//	pq "unset AAA BBB CCC"

int	ft_alpha_arr(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	return (1);
}

void	ft_delete(t_mini *ms, int here)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen_dp(ms->envp) - 1));
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
	int		i;
	char	*cut;

	i = -1;
	if (ft_alpha_arr(ms->args[1]) == -1)
		return (ft_error(101, ms->args[1]));
	while (ms->envp[++i] != NULL)
	{
		cut = ft_strdup(ms->envp[i]);
		cut[ft_pos_equal(ms->envp[i])] = '\0';
		if (ft_memcmp(cut, ms->args[1], ft_strlen(ms->args[1])) == 0)// && cut[ft_strlen(ms->args[1])] == '\0')
		{
			ft_delete(ms, i);
			free(cut);
			return (1);
		}
		free(cut);
	}
	return (0);
}
