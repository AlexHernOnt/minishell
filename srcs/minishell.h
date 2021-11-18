/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:35:00 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/18 19:06:45 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_line
{
	int				type;
	char			*content;
	struct s_line	*next;
}					t_line;

typedef struct s_mini
{
	char			**envp;

	int				o_stdin;
	int				o_stdout;

	char			**args;

	int				red_in;
	char			*in_file;
	int				fd_file_in;

	int				red_out;
	int				aph_out;
	char			*out_file;
	int				fd_file_out;

	int				pipe;
	int				pipe_influence;
	int     		pipe_fd[2];
	

	int				where_was_i;
	t_line			*list;
}					t_mini;

/*
**		M I N I S H E L L
*/

char	**ft_strdup_envp(char **envp);
void	ft_init(t_mini *ms, char **envp);
void    ft_print_list(t_mini *ms);

/*
**		E X E
*/

int		ft_pre_args(t_mini *ms);
int		ft_organizer(t_mini *ms);

int		ft_exe(t_mini *ms);
int		ft_organizer(t_mini *ms);
void    ft_cmd_no_built(t_mini *ms);

int		ft_directions(t_mini *ms);

char    *ft_path(char **envp, char **a);
void 	ft_fd_clean(t_mini *ms);

/*
**      LINE PARSING
*/

t_line	*ft_parse(char *line, t_mini *ms);
void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(void *content, int type);
int		ft_check_closed(char *line, char q);
int		ft_quotes(char *line, char c);
void	ft_expansor(t_line *line, t_mini *ms);

/*
**		ft_error
*/

int		ft_error(int code, char *arg);
void	ft_free_ms_envp(t_mini *ms);
void    ft_free_ms(t_mini *ms);

/*
**		B U I L T   I N S
*/

int		ft_echo(t_mini *ms);
int		ft_pwd(void);
int		ft_env(t_mini *ms);
int		ft_export(t_mini *ms);
int		ft_unset(t_mini *ms);
int		ft_cd(t_mini *ms);
size_t	ft_strlen_dp(char **s);
void	ft_leaks(void);


#endif
