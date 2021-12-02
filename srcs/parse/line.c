/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:36:01 by amorion-          #+#    #+#             */
/*   Updated: 2021/11/29 13:41:14 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lineadd_back(t_line **lst, t_line *new)
{
	t_line	*ptr;

	ptr = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_line	*ft_linenew(void *content, int type)
{
	t_line	*nl;

	nl = malloc(sizeof(t_line));
	if (!nl)
		return (NULL);
	nl->content = content;
	nl->type = type;
	nl->next = NULL;
	return (nl);
}

t_line	*ft_linelast(t_line *lst)
{
	t_line	*ptr;

	ptr = lst;
	if (!ptr)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}
