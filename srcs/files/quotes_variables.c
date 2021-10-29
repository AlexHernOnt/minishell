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
	int i;

	i = 1;
	while(line[i] && line[i] != q)
		i++;
	if (line[i])
		return(1);
	return(0);
}

/* Cuando entras aquí es porque has encontrado comillas simples que se cierran, 
La función devielve la longitud del espacio entre comillas -1 (incluyendolas) ya
que después la función get_content_len avanza otro valor*/

int ft_quotes(char *line)
{
	int i;
	
	i = 1;
	while(line[i] && line[i] != 39)
	{
		i++;
		//printf("%d %c\n", line[i], line[i]);
	}
	return(i);
}

/*int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	//printf("%d\n", '$');
	printf("%s\n", getenv("USER"));
	return(0);
}*/