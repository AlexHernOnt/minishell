/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:12:13 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/22 17:09:24 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Returns 1 if quotes are closed and 0 otherwise. */

int	ft_check_closed(char *line, char q)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != q)
		i++;
	if (line[i])
		return (1);
	return (0);
}

/* If entered here there are simple closed quotes. The function returns the 
*  length of the space between quotes -1 (quotes included) then get_content_len 
*  will advance the remaining space */

int	ft_quotes(char *line, char c)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

/* Removes the last element of the list if it has only spaces */

void	ft_remove_last_space(t_line *line)
{
	t_line	*ptr;
	t_line	*last;

	ptr = line;
	last = ft_linelast(line);
	if (!*(last->content) || *(last->content) == ' ')
	{
		while (ptr->next != last)
			ptr = ptr->next;
		free(ptr->next->content);
		free(ptr->next);
		ptr->next = NULL;
	}
}

/* returns the new content after removing the first set of quotes*/

char	*ft_new_content(char *old)
{
	char	*new;
	char	*aux;
	char	*ret;
	int		i;

	i = 0;
	aux = old;
	aux++;
	while (aux[i] != old[0])
		i++;
	aux[i] = 0;
	new = ft_strdup(aux);
	aux = &old[i + 2];
	ret = ft_strjoin(new, aux);
	free(new);
	return (ret);
}

/* Removes the first set of quotes in content to avoid execve errors.*/

void	ft_remove_quotes(t_line *line)
{
	t_line	*ptr;
	char	*new;

	ptr = line;
	while (ptr)
	{
		if ((*(ptr->content) == '\"' || *(ptr->content) == '\'')
			&& ft_check_closed(ptr->content, *ptr->content))
		{
			new = ft_new_content(ptr->content);
			free(ptr->content);
			ptr->content = new;
		}
		ptr = ptr->next;
	}
}
