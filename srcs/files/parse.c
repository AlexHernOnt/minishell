/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:32:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/28 16:32:19 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Se le pasa la posición en la que se está leyendo la línea y devuelve la 
longitud del primer elemento a separar siguendo las reglas de parseo de la 
shell. Y todavía sin exandir las variables, que son tratadas como caracteres 
normales. La función ignora también comillas sin cerrar y las trata como un 
caracter normal*/

int	get_content_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] !='\t')
	{
		if (line[i] == '\'' && ft_check_closed(&line[i], '\''))
			i += ft_quotes(&line[i]);
		if (line[i] == '\"' && ft_check_closed(&line[i], '\"'))
			i += ft_quotes(&line[i]);
		if (i > 0 && (line[i] == '<' || line[i] == '>' || line[i] == '|'))
			return(i);
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				return(2);
			return(1);
		}
		else if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				return(2);
			return(1);
		}
		else if (line[i] == '|')
			return(1);
		i++;
	}
	return(i);
}

/* Selecciona el tipo de un elemento de la lista dado 
(De momento está así para poder hacer pruebas) luego habrá que decidir los
tipos*/

int ft_get_type(char *line)
{
	(void)line;
	return(0);
}

/*Lee la línea y la transforma en una lista separándola por tipo
(palabra variable operador...) primero obtiene la longitud del
primer elemento, después copia el contenido de la línea en content
y lo añade a la lista. Seleccionando el tipo de elemento que es.
Finalmente se desplaza la longitud del elemento para comprobar el 
siguiente.
PENDIENTE DE SOLUCIÓN: 
	*Crear un expansor, que recorra la lista cambiando 
	$x por su valor cuando no esté entre ' '
	*Reconocer los comandos (Esto dependerá de si debemos coger comandos de fuera)
	de ser así se haría como en pipex posteriormente, por lo que no sería 
	necesario*/

t_line  *ft_parse(char *line)
{
	t_line *list_line;
	int len;
	int i;
	char *tmp;
	if (!line)
		return(NULL);
	list_line = NULL;
	i = 0;
	while(line[i])
	{
		if ((i > 0 && line[i-1]) || i == 0)
		{
			len = get_content_len(&line[i]);
			tmp = ft_strdup(&line[i]);
			tmp[len]=0;
			//printf("line %s\ntemp %s\n", &line[i], tmp);
			ft_lineadd_back(&list_line, ft_linenew(ft_strdup(tmp), ft_get_type(&line[i])));
			free(tmp);
			i += len + (line[i+len] == ' '); //si lo siguiente es un espacio avanza 1 más si no no, esto es para gestionar cosas como >cosas.
		}
		else 
			break;
	}
	return(list_line);
}

/*int main(int argc, char **argv)
{
	t_line *list;
	char *str;
	(void)argc;
	(void)argv;
	str = "Hola esto | tiene <<comillas simples'con espacios pipes | y un operador >>  >y variable $1 dentro' y con comillas dobles\"como estas\" ";
	list = ft_parse(str);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	return(0);
}*/