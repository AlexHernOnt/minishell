/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 18:34:29 by amorion-          #+#    #+#             */
/*   Updated: 2021/08/03 09:32:16 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getlen(int n)
{
	int	len;
	int	num;

	num = n;
	len = 0;
	if (n < 0)
		len = 1;
	while (num / 10)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static int	treatnum(int n, int *last, char *str)
{
	if (n == -2147483648)
	{
		str[1] = '2';
		n = -147483648;
		*last = 2;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n == 0)
		str[0] = '0';
	return (n);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		last;

	last = 0;
	len = ft_getlen(n);
	str = malloc(sizeof(char) * (len + 2));
	if (!str)
		return (NULL);
	str[len + 1] = 0;
	n = treatnum(n, &last, str);
	while (len >= last && n != 0)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len --;
	}
	return (str);
}
