/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:57:43 by amorion-          #+#    #+#             */
/*   Updated: 2021/11/10 18:01:08 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_var(char *element)
{
	int	i;

	i = 0;
	while (element[i])
	{
		if (element[i] == '\'' && ft_check_closed(&element[i], '\''))
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

/* Busca la primera variable ignorando '' si la encuentra divide la cadena
La parte inicial, es lo que hay antes del $, luego la parte central en la que
se expande la variable y el resto de la cadena. Después une las tres parte y la 
retorna. 
PENDIENTE:
	acortar para norma
	coger nuestro environment en vez de getenv*/


char	*ft_getenv(char *aux, t_mini *ms)
{
	char	*new;
	int		i;

	i = 0;
	while (ms->envp[i] != NULL)
	{
		if (ft_memcmp(aux, ms->envp[i], ft_strlen(aux)) == 0
				&& ms->envp[i][ft_strlen(aux)] == '=')
			return (ft_strdup(ms->envp[i]) + ft_strlen(aux) + 1);
		i++;
	}
	return (NULL);
}

char	*ft_expand(char *content, t_mini *ms)
{
	int		i;
	int		n;
	char	*new;
	char	*aux;
	char	*aux2;

	i = 0;
	n = 0;
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
			new = ft_strdup(aux);
			i++;
			while (content[i + n] && content[i + n] != ' '
				&& content[i + n] != '\"' && content[i + n] != '\'')
			{
				aux[n] = content[i + n];
				n++;
			}
			aux[n] = 0;
			aux2 = ft_getenv(aux, ms); 
			free(aux);
			if (aux2)	//AAAAAAAAAaaAAAAAAAAAaaaaAAA LIBERAR AUX 2 HAAHAHAHHAAaAhahAhahah
			{
				free(new);
				new = ft_strjoin(new, aux2);
			}
			free(new);
			new = ft_strjoin(new, &content[i + n]);
			free(content);
			return (new);
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
		{
			ptr->content = ft_expand(ptr->content, ms);
		}
		ptr = ptr->next;
	}
}

/**int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *str = "Content: simples'con espacios pipes | y un operador >> 
	> y variable $1 dentro'" ;
	printf("%d\n", ft_is_var(str));
	return(0);
}*/
