/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:56:27 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/01 18:15:50 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	HEY YOU!, listen, u only can pass this function individual strings, with no spaces,
//	split them and send them first
//	pq "export AAA=1 BBB=2 CCC=3"


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
		new_envp[i] = NULL;
//		ft_free_ms_envp(ms);

		for (int z = 0; new_envp[z] != NULL; z++)
			printf("_%s_\n", new_envp[z]);

		printf("hello!!!?????\n");
		ms->envp = new_envp;
	}
}

int	ft_unset(t_mini *ms, char *aux)
{
	int		i;
	char	*str;
	char	**new_envp;

	i = 0;
	str = ft_strdup(aux + 6);
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp(ms->envp[i], str, ft_strlen(str)) > 0)
		{
			printf("_%d_\n", i);
			ft_delete(ms, str, i);
			free(str);
			return (1);
		}
		i++;
	}
	free(str);
	return (0);
}
