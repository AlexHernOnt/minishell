/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:37:12 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/10 18:26:12 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exe(char *aux, t_mini *ms)
{
	if (ft_memcmp(aux, "echo", 4) == 0)
		ft_echo(aux, 0);
	else if (ft_memcmp(aux, "cd", 2) == 0)
		ft_cd(aux);
	else if (ft_memcmp(aux, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_memcmp(aux, "env", 3) == 0)
		ft_env(ms);
	else if (ft_memcmp(aux, "export", 6) == 0)
		ft_export(ms, aux);
	else if (ft_memcmp(aux, "unset", 5) == 0)
		ft_unset(ms, aux);
	else if (ft_memcmp(aux, "exit", 4) == 0)
		return (0);
	else
		if (aux[0] != '\0')
			printf("-minishell: %s: Comand not found\n", aux);
	return (1);
}
