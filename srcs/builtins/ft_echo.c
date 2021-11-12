/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:44:56 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/12 19:01:21 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_mini *ms)
{
	int	i;

	i = 1;

	if (ms->args[1][2])
		printf("asdasd\n");

	if (ms->args[1][0] == '-' && ms->args[1][1] == 'n' && ms->args[1][2] == '\n')
	{
		i++;
		printf("Flavia!\n");
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

/*
**	O L D
*/

/*
int	ft_echo(char *line, int arg_n)
{
	char	*clean_line;

	if (arg_n == 0)
		clean_line = ft_strdup(line + 5);
	else
		clean_line = ft_strdup(line + 8);
	printf("%s", clean_line);
	if (arg_n == 0)
		printf("\n");
	free(clean_line);
	return (1);
}
*/
