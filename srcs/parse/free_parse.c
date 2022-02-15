/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 09:57:11 by amorion-          #+#    #+#             */
/*   Updated: 2022/02/15 09:57:14 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_var(char *aux2, char *aux, char *content)
{
	if (aux2)
		free(aux2);
	if (aux)
		free(aux);
	if (content)
		free(content);
}
