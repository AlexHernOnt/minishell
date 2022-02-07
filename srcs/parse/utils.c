/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:47:03 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/24 10:47:05 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Returns the numbber of spaces in the line before other characters

int	ft_ispace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' ))
		i++;
	return (i);
}

/* Returns 1 if an operator is found*/
int	ft_is_operator(t_line *ptr)
{
	if (ptr->content[0] == '<' || ptr->content[0] == '>'
		|| ptr->content[0] == '|')
		return (1);
	return (0);
}

/* Returns 1 if it finds a variable */

int	ft_is_var(char *element)
{
	int	i;
	int	dc;

	i = 0;
	while (element[i])
	{
		if (element[i] == '\"')
			dc = -dc;
		if (element[i] == '\'' && ft_check_closed(&element[i], '\'') && dc < 0)
		{
			i++;
			while (element[i] != '\'')
				i++;
			i++;
		}
		if (element[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_only_spaces(char *aux)
{
	while (*aux != '\0')
	{
		if (*aux != ' ' && *aux != '\t')
			return (0);
		aux++;
	}
	return (1);
}

int	ft_pipe_sintax(t_line *ptr, t_line *line)
{
	if (ptr != line)
	{
		ptr->type = 5;
		return (0);
	}
	return (1);
}
