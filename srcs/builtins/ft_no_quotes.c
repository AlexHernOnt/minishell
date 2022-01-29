/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:48:00 by amorion-          #+#    #+#             */
/*   Updated: 2022/01/29 17:48:02 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(t_mini *ms, int j)
{
	int		i;

	i = 0;
	while (ms->args[j][i] != '\0' && ms->args[j][i] != '=')
		i++;
	if (ms->args[j][i] == '=')
		return (i + 1);
	return (0);
}

void	ft_no_quotes(t_mini *ms, int j, char type)
{
	char	*new;
	int		i;
	int		k;

	k = 0;
	if (ms->args[j][0] && ms->args[j][find_equal(ms, j)] == type &&
		ms->args[j][ft_strlen(ms->args[j]) - 1] == type)
	{
		new = malloc(ft_strlen(ms->args[j]) - find_equal(ms, j) - 2 + 1);
		i = find_equal(ms, j) + 1;
		ms->args[j][i - 1] = 0;
		if (new)
		{
			while (ms->args[j][i] != type)
			{
				new[k] = ms->args[j][i];
				i++;
				k++;
			}
			new[k] = '\0';
			free(ms->args[j]);
			ms->args[j] = ft_strjoin(ms->args[j], new);
			free(new);
		}
	}
}
