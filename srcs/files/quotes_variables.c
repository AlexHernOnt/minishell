/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:57:43 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/29 09:57:45 by amorion-         ###   ########.fr       */
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

int	ft_quotes(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != 39)
		i++;
	return (i);
}

/* Recorre content y determina si hay variabes, excluyendo los $ entre 
comillas simples*/

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
	acortar para norma*/

char	*ft_expand(char *content)
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
			aux2 = getenv(aux);
			free(aux);
			if (aux2)
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
encontrar un elemento con varables las expande llaando iterativamente a 
ft_expand mientras queden, retorna la nueva cadena*/

void	ft_expansor(t_line *line)
{
	t_line	*ptr;

	ptr = line;
	while (ptr)
	{
		while (ft_is_var(ptr->content))
		{
			ptr->content = ft_expand(ptr->content);
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