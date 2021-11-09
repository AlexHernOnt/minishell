/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:32:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/11/08 17:16:27 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Se le pasa la posición en la que se está leyendo la línea y devuelve la 
**	longitud del primer elemento a separar siguendo las reglas de parseo de la 
**	shell. Y todavía sin exandir las variables, que son tratadas como caracteres 
**	normales. La función ignora también comillas sin cerrar y las trata como un 
**	caracter normal
*/

int	get_content_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		if (line[i] == '\'' && ft_check_closed(&line[i], '\''))
			i += ft_quotes(&line[i]);
		if (line[i] == '\"' && ft_check_closed(&line[i], '\"'))
			i += ft_quotes(&line[i]);
		if (i > 0 && (line[i] == '<' || line[i] == '>' || line[i] == '|'))
			return (i);
		else if (line[i] == '<' || line[i] == '>')
		{
			if (line[i + 1] == line[i])
				return (2);
			return (1);
		}
		i++;
	}
	return (i);
}

//	Devuelve el número de espacios al comienzo de line

int	ft_ispace(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' ))
		i++;
	return (i);
}

/*
	Selecciona el tipo de un elemento de la lista dado 
	(De momento está así para poder hacer pruebas) luego habrá que decidir los
	tipos.

	exe nuestro,
	exe suyo,
	
*/

/* Recorre la lista asignando un tipo a cada elemento
tipos:
0 = infile/pwd
1 = <
2 = <<
3 = comand
4 = argument
5 = |
6 = >
7 = >>
8 Outfile*/
int ft_is_operator(t_line *ptr)
{
	if (ptr->content[0] == '<' || ptr->content[0] == '>' || ptr->content[0] == '|')
		return (1);
	return (0);
}

int	ft_get_type(t_line *line)
{
	t_line *ptr;

	ptr = line;
	while(ptr)
	{
		//printf("content: %s\n", ptr->content);
		if(ptr->content[0] == '<')
		{
			ptr->next->type = 0;
			if (ptr->content[1] == '<')
				ptr->type = 2;
			else if(ptr->content[1] == 0) 
				ptr->type = 1;
		}
		if (ptr->content[0] == '|')
			ptr->type = 5;
		if (ptr->content[0] == '>')
		{
			ptr->next->type = 8;
			if (ptr->content[1] == '>')
				ptr->type = 7;
			else if(ptr->content[1] == 0)
				ptr->type = 7;
		}
		if (ptr->type == -1)
		{
			ptr->type = 3;
			ptr = ptr->next;
			while(ptr && !ft_is_operator(ptr))
			{
				ptr->type = 4;
				ptr = ptr->next;
			}
		}
		else
			ptr = ptr->next;
	}
	return (0);
}

/*Lee la línea y la transforma en una lista separándola por tipo
(palabra variable operador...) primero obtiene la longitud del
primer elemento, después copia el contenido de la línea en content
y lo añade a la lista. Todo ello ignorando separadores seguidos. Seleccionando 
el tipo de elemento que es.
Finalmente se desplaza la longitud del elemento para comprobar el 
siguiente.
PENDIENTE DE SOLUCIÓN: 
	*recortar función del expansor para pasar la norma
	*Reconocer los comandos (Esto dependerá de si debemos coger comandos de fuera)
	de ser así se haría como en pipex posteriormente, por lo que no sería 
	necesario
	*Demmasiado larga, el while pasa a ser otra función ft_get_line*/

t_line *ft_parse(char *line, t_mini *ms)
{
	t_line	*list_line;
	int		len;
	int		i;
	char	*tmp;

	if (!line)
		return (NULL); // El número que sea
	list_line = NULL;
	i = 0;
	while (line[i])
	{
		if ((i > 0 && line[i - 1]) || i == 0)
		{
			i += ft_ispace(&line[i]);
			len = get_content_len(&line[i]);
			tmp = ft_strdup(&line[i]);
			tmp[len] = 0;
			ft_lineadd_back(&list_line, ft_linenew(ft_strdup(tmp), -1));
			free(tmp);
			i = i + len + ft_ispace(&line[i]);
		}
		else
			break ;
	}
	ft_expansor(list_line, ms);
	ft_get_type(list_line);
	return (list_line);
}

int main(int argc, char **argv)
{
	t_line *list;
	t_line *ptr;
	char *str;

	(void)argc;
	(void)argv;
	str = "Hola esto | $usdghgs tiene a<<comillas simples'con espacios pipes | y un operador >>  >y variable $test dentro' y con comillas dobles\"como estas $test $test\" ";
	printf("%s\n\n", str);
	list = ft_parse(str);
	while (list)
	{
		printf("Content: _%s_\t\t : Type %d\n", list->content, list->type);
		ptr = list->next;
		free(list->content);
		free(list);
		list = ptr;
	}
//	system("leaks a.out");
	return(0);
}
