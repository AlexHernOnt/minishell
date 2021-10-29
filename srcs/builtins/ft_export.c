/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:21:48 by ahernand          #+#    #+#             */
/*   Updated: 2021/10/29 18:15:20 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_DELETE(char const *str)
{
	char	*cpy;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	cpy = malloc(sizeof(*cpy) * (ft_strlen(str) + 1));
	if (!cpy)
		return (NULL);
	while (str[i])
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}

size_t	ft_strlen_big(char **s)
{
	int		i;

	i = 0;
	while (s[i] != NULL)
		i++;

	return (i);
}

char	**ft_export(char *aux, char **envp)
{
	int		i;
	char	*str;
	char	**new_envp;

	i = 0;
	str = ft_strdup_DELETE(aux + 7);
	new_envp = malloc(sizeof(char**) * ft_strlen_big(envp) + 2);
	if (!new_envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = str;
	new_envp[i + 1] = NULL;
	free(str);
	envp = new_envp;
	return (new_envp);
}
