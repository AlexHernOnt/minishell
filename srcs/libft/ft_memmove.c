/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:07:41 by amorion-          #+#    #+#             */
/*   Updated: 2021/07/31 15:58:19 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*aux;
	char		*dest_c;
	size_t		i;

	aux = src;
	dest_c = dest;
	if (src < dest)
		while (n--)
			dest_c[n] = aux[n];
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			dest_c[i] = aux[i];
			i++;
		}
	}
	return (dest);
}
