/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:          <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:59:09 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/01 17:55:32 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct		s_line
{
	int				type;
	char			*content;
	struct s_line 	*next;
}					t_line;

typedef struct		s_mini
{
	char			**envp;
}					t_mini;


/*
**		B U I L T   I N S
*/

int     ft_echo(char *line, int arg_n);
int     ft_pwd(void);
int     ft_env(t_mini *ms);
int		ft_export(t_mini *ms, char *aux);
int		ft_unset(t_mini *ms, char *aux);
int 	ft_cd(char *dir);

size_t	ft_strlen_dp(char **s);
void	ft_leaks();

//		Export

void    ft_free_ms_envp(t_mini *ms);

/*
**      LINE PARSING
*/

void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(void *content, int type);
int     ft_check_closed(char *line, char q);
int		ft_quotes(char *line);

#endif
