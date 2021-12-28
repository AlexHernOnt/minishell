/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:44:56 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 18:08:15 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Devuelve el mismo retorno que el echo original (0 success/>0failure)

int	all_n_baby(char *str)
{
	int	i;

	i = 1;
	if (str && str[0] == '-' && str[1] != '\0')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(t_mini *ms)
{
	int	i;
	int	si;

	i = 1;
	si = 0;
	if (!ms->args[1])
		return (0);
	while (all_n_baby(ms->args[i]) == 1)
	{
		si = 1;
		i++;
	}
	while (ms->args[i] != NULL)
	{
		if (ms->args[i + 1] == NULL)
			printf("%s", ms->args[i]);
		else
			printf("%s ", ms->args[i]);
		i++;
	}
	if (!si)
		printf("\n");
	return (0);
}
