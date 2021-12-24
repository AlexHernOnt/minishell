/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:35:00 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/06 14:04:04 by ahernand         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_line
{
	int				type;
	char			*content;
	struct s_line	*next;
}					t_line;

typedef struct s_mini
{
	int				ret;		//variable retorno $?

	char			**envp;
	int				export_pos;

	int				o_stdin;
	int				o_stdout;

	char			**args;

	int				append;


	int				in_cs;
	int     		pipe_cs[2];


	int				n_in_max;
	int				n_in_cur;

	int				red_in;
	char			*in_file;
	int				fd_file_in;


	int				n_out_max;
	int				n_out_cur;

	int				red_out;
	int				aph_out;
	char			*out_file;
	int				fd_file_out;


	int				pipe;
	int				p_first;
	int				p_last;
	int				p_done;

	int				p_b_exists;

	char			p_using;
	int     		pipe_fd_a[2];
	int     		pipe_fd_b[2];

	int				exit;

	int				where_was_i;
	t_line			*list;
	int				exit_status;
}					t_mini;

int g_id;
/*
*	Readline.h
*/
extern void rl_replace_line(const char *, int);
extern void rl_clear_history(void);


/*
**		M I N I S H E L L
*/

extern void rl_clear_history(void);


char	**ft_strdup_envp(char **envp);
void	ft_init(t_mini *ms, char **envp);
void    ft_print_list(t_mini *ms);
int		ft_only_spaces(char *aux);
void	ft_free_list(t_mini *ms);

/*
**		E X E
*/

int		ft_pre_args(t_mini *ms);
int		ft_organizer(t_mini *ms);

int		ft_exe(t_mini *ms);
int		ft_organizer(t_mini *ms);
int		ft_cmd_no_built(t_mini *ms);

int		ft_directions(t_mini *ms);

char    *ft_path(char **envp, char **a);
void 	ft_fd_clean(t_mini *ms);

int		ft_pipes(t_mini *ms);


int		file_in(t_mini *ms);
int		file_out(t_mini *ms);

/*
**      LINE PARSING
*/

t_line	*ft_parse(char *line, t_mini *ms);
void	ft_lineadd_back(t_line **lst, t_line *new);
t_line	*ft_linenew(void *content, int type);
t_line	*ft_linelast(t_line *lst);
int		ft_check_closed(char *line, char q);
int		ft_quotes(char *line, char c);
void	ft_remove_quotes(t_line *line);
void	ft_expansor(t_line *line, t_mini *ms);
void	ft_remove_last_space(t_line *line);
int		ft_ispace(char *line);
int		ft_is_operator(t_line *ptr);
int		ft_is_var(char *element);

/*
**		ft_error
*/

int		ft_error(t_mini *ms, int code, char *arg);
void	ft_free_ms_envp(t_mini *ms);
void    ft_free_ms(t_mini *ms);
void	ft_free_line(t_line **line);

/*
**		B U I L T   I N S
*/

int		ft_echo(t_mini *ms);
int		ft_pwd(void);
int		ft_env(t_mini *ms);

int 	ft_doer_unset(t_mini *ms, int j);
int		ft_unset(t_mini *ms);
int		ft_pos_equal(char *str);
void	ft_delete(t_mini *ms, int here);


/*
**		FT_EXPORT
*/

int		ft_export(t_mini *ms);
int		ft_doer_export(t_mini *ms, int j);
int		ft_check_equal(char *str);
int		ft_alredy_exists(t_mini *ms, int j);
size_t	ft_strlen_dp(char **s);



int		ft_cd(t_mini *ms);
size_t	ft_strlen_dp(char **s);
void	ft_leaks(void);
 
/*
** 	CTRL C	& CTRL \
*/

void 	ft_blocking(int sig);
void	ft_ctrl(int sig);
int		ft_ctrld(char *aux, t_mini *ms);
#endif
