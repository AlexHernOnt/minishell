/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 11:19:44 by amorion-          #+#    #+#             */
/*   Updated: 2022/02/05 11:19:47 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote_scape(char *content, int i)
{
	i++;
	while (content[i] && content[i] != '\'')
		i++;
	return (i);
}

t_line	*ft_scape_args(t_line *line)
{
	t_line	*ptr;

	ptr = line;
	while (ptr->next && !ft_is_operator(ptr))
	{
		ptr->next->type = 4;
		ptr = ptr->next;
	}
	return (ptr->next);
}
