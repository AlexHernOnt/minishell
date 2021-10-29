/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:          <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:09 by ahernand          #+#    #+#             */
/*   Updated: 2021/10/27 18:03:25 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_line
{
	int type;
	char *content;
	struct s_line *next;
} t_line;

/*
**		B U I L T   I N S
*/

int     ft_echo(char *line, int arg_n);
int     ft_pwd(void);
int     ft_env(char **envp);
int 	ft_cd(char *dir);

/*
**      LINE PARSING
*/

void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(void *content, int type);
int     ft_check_closed(char *line, char q);
int		ft_quotes(char *line);

/*
**		L I B F T	
*/

char    *ft_strdup(char const *str);
size_t  ft_strlen(const char *s);
#endif
