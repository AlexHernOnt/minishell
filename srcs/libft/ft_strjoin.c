/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:45:13 by amorion-          #+#    #+#             */
/*   Updated: 2021/08/03 17:54:52 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char const *s1, char const *s2)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s1[size])
		size++;
	while (s2[i])
		i++;
	size = size + i;
	return (size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		size;
	char	*str;

	size = ft_size(s1, s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	size = 0;
	while (s2[size])
	{
		str[i + size] = s2[size];
		size++;
	}
	str[i + size] = '\0';
	return (str);
}
