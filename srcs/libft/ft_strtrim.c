/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtirm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 09:58:58 by amorion-          #+#    #+#             */
/*   Updated: 2021/08/02 11:15:03 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set [i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_strlen_mod(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	wstr(char *str, char const *s1, int i, int size)
{
	int	n;

	n = 0;
	while (n < size)
	{
		str[n] = s1[i + n];
		n++;
	}
	str[n] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		size;
	char	*str;

	size = ft_strlen_mod(s1);
	i = 0;
	while (ft_isinset(set, s1[size - 1]) && size)
		size--;
	while (ft_isinset(set, s1[i]))
	{
		size--;
		i++;
	}
	if (size <= 0)
		size = 0;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	wstr(str, s1, i, size);
	return (str);
}
