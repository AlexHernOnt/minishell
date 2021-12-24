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

/* Comprueba que las comillas estén cerradas devuelve 1 si es así y 0 en caso 
contrario*/

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

/* Cuando entras aquí es porque has encontrado comillas simples que se cierran, 
La función devielve la longitud del espacio entre comillas -1 (incluyendolas) ya
que después la función get_content_len avanza otro valor*/

int	ft_quotes(char *line, char c)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}

/* elminia el último elemento de la lista si solo contiene espacios */

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
		if (*(ptr->content) == '\"' || *(ptr->content) == '\'')
		{
			new = ft_new_content(ptr->content);
			free(ptr->content);
			ptr->content = new;
		}
		ptr = ptr->next;
	}
}
