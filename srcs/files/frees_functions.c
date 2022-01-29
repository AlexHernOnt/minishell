/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 16:46:59 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 16:48:52 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_ms(t_mini *ms)
{
	int	i;
	
	i = 0;
	while (ms->args[i] != NULL)
	{
		if (ms->args[i])
		{
			free(ms->args[i]);
			ms->args[i] = NULL;
		}
		i++;
	}
	if (ms->args != NULL)
		free(ms->args);
	ms->args = NULL;
}

void	ft_free_ms_envp(t_mini *ms)
{
	int	i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		free(ms->envp[i]);
		ms->envp[i] = NULL;
		i++;
	}
	free(ms->envp);
	ms->envp = NULL;
}

void	ft_free_list(t_mini *ms)
{
	t_line		*ptr;
	t_line		*aux;

	ptr = ms->list;
	while (ptr != NULL)
	{
		aux = ptr->next;
		if (ptr->content)
			free(ptr->content);
		if (ptr)
			free(ptr);
		ptr = aux;
	}
}

/* Frees the line in case of parsing error*/
void	ft_free_line(t_line **line)
{
	t_line	*ptr;

	while (*line)
	{
		ptr = *line;
		free(ptr->content);
		*line = ptr->next;
		free(ptr);
	}
}
