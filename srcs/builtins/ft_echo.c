/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:44:56 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/06 17:08:27 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Devuelve el mismo retorno que el echo original (0 success/>0failure)
int	ft_echo(t_mini *ms)
{
	int	i;
	int	si;

	i = 1;
	si = 0;
	if (!ms->args[1])
		return (0);
	while (ms->args[i] && ms->args[i][0] == '-' && ms->args[i][1] == 'n' && ms->args[i][2] == '\0')
	{
		si = 1;
		i++;
	}
	while (ms->args[i])
	{
		if (ms->args[i + 1] && ms->args[i + 1] == NULL)
			printf("%s", ms->args[i]);
		else
			printf("%s ", ms->args[i]);
		i++;
	}
	if (!si)
		printf("\n");
	return (0);
}
