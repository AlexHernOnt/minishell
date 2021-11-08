/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:12:09 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/08 17:38:17 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_leaks(void)
{
	system("leaks minishell");
}

int	ft_error(int code, char *arg)
{
	if (code == 101)
		printf("-minishell: unset: `%s': not a valid identifier\n", arg);
	return (-1);
}
