/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:44:56 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/23 14:34:04 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_mini *ms)
{
	int	i;

	i = 1;
	if (!ms->args[1])
	{
		printf("\n");
		return (-1);
	}
	if (ms->args[1][0] == '-' && ms->args[1][1] == 'n' && ms->args[1][2] == '\0')
	{
		i++;
	}
	while (ms->args[i] != NULL)
	{
		if (ms->args[i + 1] && ms->args[i + 1] == NULL)
			printf("%s", ms->args[i]);
		else
			printf("%s ", ms->args[i]);
		i++;
	}
	if (ms->args[1][0] != '-' && ms->args[1][1] != 'n' && ms->args[1][2] != '\n')
		printf("\n");
	return (1);
}
