/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:08:04 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/12 18:15:27 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**		Read File
*/

int	ft_full_route(char *str)
{
	if (str[0] == '/')
	{
		if (access(str, F_OK) == 0)
			return (1);
	}
	return (-1);
}

int	ft_path_pos(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_fix_first(char **list_paths)
{
	int		i;
	int		l;
	char	*new;

	i = 0;
	l = ft_strlen(list_paths[0]);
	new = malloc(sizeof(char) * (l + 1 - 5));
	if (!new)
		return (NULL);
	new[l - 5] = '\0';
	while (i < l - 5)
	{
		new[i] = list_paths[0][i + 5];
		i++;
	}
	new[i] = '\0';
	free(list_paths[0]);
	return (new);
}

char	*ft_good_path(char **list_paths, char *cmd)
{
	int		i;
	char	*aux;
	char	*aux2;

	i = 0;
	if (!cmd)
		return (NULL);
	while (list_paths[i])
	{
		aux = ft_strjoin(list_paths[i], "/");
		aux2 = ft_strjoin(aux, cmd);
		if (access(aux2, F_OK) == 0)
		{
			if (aux != NULL)
				free(aux);
			return (aux2);
		}
		if (aux != NULL)
			free(aux);
		if (aux2 != NULL)
			free(aux2);
		i++;
	}
	return (NULL);
}

char	*ft_path(char **envp, char **a)
{
	int		i;
	int		i_pos;
	char	*new;
	char	**list_paths;

	i = 0;
	i_pos = ft_path_pos(envp);
	list_paths = ft_split(envp[i_pos], ':');
	list_paths[0] = ft_fix_first(list_paths);
	if (ft_full_route(a[0]) == -1)
		new = ft_good_path(list_paths, a[0]);
	else
		new = ft_strdup(a[0]);
	while (list_paths[i] != NULL)
	{
		free(list_paths[i]);
		i++;
	}
	free(list_paths);
	if (new == NULL)
		return (a[0]);
	free(a[0]);
	return (new);
}
