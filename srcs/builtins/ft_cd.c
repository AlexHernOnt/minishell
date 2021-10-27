/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:08:14 by ahernand          #+#    #+#             */
/*   Updated: 2021/10/27 17:34:53 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *dir)
{
	char	*clean_dir;

	clean_dir = ft_strdup(dir + 3);
	chdir(clean_dir);
	free(clean_dir);
	return (1);
}
