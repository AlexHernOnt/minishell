/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:56:27 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/02 17:18:58 by ahernand         ###   ########.fr       */
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

void	ft_delete(t_mini *ms, char *aux, int here)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * ft_strlen_dp(ms->envp) - 1);
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

int	ft_unset(t_mini *ms, char *aux)
{
	int		i;
	char	*str;
	char	*cut;
	char	**new_envp;

	i = -1;
	str = ft_strdup(aux + 6);
	if (ft_alpha_arr(str) == -1)
		return (ft_error(101, str));
	while (ms->envp[++i] != NULL)
	{
		cut = ft_strdup(ms->envp[i]);
		cut[ft_pos_equal(ms->envp[i])] = '\0';
		if (ft_memcmp(cut, str, ft_strlen(str)) >= 0)
		{
			ft_delete(ms, str, i);
			free(str);
			free(cut);
			return (1);
		}
		free(cut);
	}
	free(str);
	return (0);
}
