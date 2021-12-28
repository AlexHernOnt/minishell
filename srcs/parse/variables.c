/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:57:43 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/28 17:08:04 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Returns the value of the variable aux*/

char	*ft_getenv(char *aux, t_mini *ms)
{
	int		i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp(aux, ms->envp[i], ft_strlen(aux)) == 0
			&& ms->envp[i][ft_strlen(aux)] == '=')
			return (ft_strdup(&(ms->envp[i][ft_strlen(aux) + 1])));
		i++;
	}
	return (NULL);
}

/* Expands the return value when found $?*/

char	*ft_return_value(t_mini *ms, char *aux, int i)
{
	char	*new;
	char	*aux2;

	aux2 = ft_itoa(ms->exit_status);
	new = ft_strjoin(aux, aux2);
	free(aux2);
	free(new);
	new = ft_strjoin(new, &aux[i + 1]);
	free(aux);
	return (new);
}

/* Expands variables that are different from $?*/

char	*ft_other_variable(t_mini *ms, char *aux, char *content, int i)
{
	char	*new;
	char	*aux2;
	int		n;

	n = 0;
	new = ft_strdup(aux);
	while (content[i + n] && content[i + n] != ' ' && content[i + n] != '\"'
		&& content[i + n] != '\'' && content[i + n] != '/')
	{
		aux[n] = content[i + n];
		n++;
	}
	aux[n] = 0;
	aux2 = ft_getenv(aux, ms);
	free(aux);
	if (aux2)
	{
		free(new);
		new = ft_strjoin(new, aux2);
		free(aux2);
	}
	free(new);
	new = ft_strjoin(new, &content[i + n]);
	free(content);
	return (new);
}

/* Finds the first vaariable ignoring ''. If a variable is found it divides the
*  string i three and expands the variable in the middle part, then joins and
*  returns the string. If no variable is found it returns NULL.*/

char	*ft_expand(char *content, t_mini *ms)
{
	int		i;
	char	*aux;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\'' && ft_check_closed(&content[i], '\''))
		{
			i++;
			while (content[i] != '\'')
				i++;
		}
		if (content[i] == '$')
		{
			aux = ft_strdup(content);
			aux[i] = 0;
			free(content);
			if (content[i + 1] == '?')
				return (ft_return_value(ms, aux, i + 1));
			else
				return (ft_other_variable(ms, aux, ft_strdup(content), i + 1));
		}
		i++;
	}
	return (content);
}

/* Recorre la lista, detecta si un elemento contiene variables y al 
encontrar un elemento con varables las expande llamando iterativamente a 
ft_expand mientras queden, retorna la nueva cadena*/

void	ft_expansor(t_line *line, t_mini *ms)
{
	t_line	*ptr;

	ptr = line;
	while (ptr)
	{
		while (ft_is_var(ptr->content))
			ptr->content = ft_expand(ptr->content, ms);
		ptr = ptr->next;
	}
}
