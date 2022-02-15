/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:35:00 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 17:06:36 by ahernand         ###   ########.fr       */
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
# include <termios.h>
# include <errno.h>

typedef struct s_line
{
	int				type;
	char			*content;
	struct s_line	*next;
}					t_line;

typedef struct s_mini
{
	char			**envp;
	int				export_pos;

	int				o_stdin;
	int				o_stdout;

	char			**args;

	int				append;

	int				in_cs;
	int				pipe_cs[2];

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

	int				pipe_to_use;
	int				**pipes_fds;

	int				exit;

	int				where_was_i;
	t_line			*list;
	int				exit_status;
}					t_mini;

typedef struct s_tcattr
{
	struct termios	original;
	struct termios	ctrl_c;
}					t_tcattr;

int		g_id;

/*
**				Readline.h
*/

extern void		rl_replace_line(const char *iii, int i);
extern void		rl_clear_history(void);

/*
**				M I N I S H E L L
*/

char			**ft_strdup_envp(char **envp);
void			ft_init(t_mini *ms, char **envp);
void			ft_print_list(t_mini *ms);
int				ft_only_spaces(char *aux);
void			ft_free_list(t_mini *ms);

/*
**				builting_hub
*/

int				ft_single_cmd(t_mini *ms);
int				ft_exe_2(t_mini *ms);
int				builtins_hub(t_mini *ms, int i, int lock);
int				ft_built_in(t_mini *ms);

/*
**				ft_exe
*/

int				ft_exe(t_mini *ms);
int				ft_exe_exit(t_mini *ms);
void			ft_fd_clean(t_mini *ms);
void			ft_redir_clean(t_mini *ms);

/*
**				ft_cmd_no_builtin
*/

int				ft_cmd_no_builtin(t_mini *ms);
void			ft_parent(t_mini *ms);
int				ft_child(t_mini *ms, t_line *ptr, int i);

/*
**				ft_organizer
*/

int				ft_organizer(t_mini *ms);
int				ft_pre_args(t_mini *ms, t_line **ptr);
int				ft_alloc_args(t_mini *ms, int i);
void			ft_clear_for_next_line(t_mini *ms);
void			ft_clear_next_segment(t_mini *ms);
void			ft_clear_for_next_line(t_mini *ms);
int				ft_in_fork(t_mini *ms, t_line **ptr, int *i);

/*
**				ft_collect_info_line
*/

int				ft_collect_info_line(t_mini *ms, t_line **ptr, int *i);
void			ft_num_of_infiles(t_mini *ms, t_line **ptr);
int				ft_collect_cs(t_mini *ms, t_line **ptr);
void			ft_num_of_outfiles(t_mini *ms, t_line **ptr);

/*
**				ft_directions
*/

int				ft_directions(t_mini *ms);
void			ft_input_source(t_mini *ms);
int				ft_cs(t_mini *ms);
int				abs_memcmp(char *arr1, char *arr2);

/*
**				ft_pipes
*/

int				ft_pipes(t_mini *ms);
int				ft_middle_pipe(t_mini *ms);
void			ft_finish_pipe(t_mini *ms);

char			*ft_path(char **envp, char **a);

int				file_in(t_mini *ms, t_line *ptr);
int				file_out(t_mini *ms, t_line *ptr);

/*
**				ft_pipe_work
*/

void			ft_close_all_fd(t_mini *ms);
void			ft_start_pipe(t_mini *ms, t_line **ptr);
void			ft_pipes_opening(t_mini *ms, t_line **ptr);
void			ft_next_pipe(t_mini *ms, t_line **ptr);

/*
**				LINE PARSING
*/

t_line			*ft_parse(char *line, t_mini *ms);
void			ft_lineadd_back(t_line **lst, t_line *new);
t_line			*ft_linenew(void *content, int type);
t_line			*ft_linelast(t_line *lst);
int				ft_check_closed(char *line, char q);
int				ft_quotes(char *line, char c);
void			ft_remove_quotes(t_line *line);
void			ft_expansor(t_line *line, t_mini *ms);
void			ft_remove_last_space(t_line *line);
int				ft_ispace(char *line);
int				ft_is_operator(t_line *ptr);
int				ft_is_var(char *element);
int				ft_pipe_sintax(t_line *ptr, t_line *line);
int				ft_quote_scape(char *content, int i);
t_line			*ft_scape_args(t_line *line);

/*
**				ft_error
*/

int				ft_error(t_mini *ms, int code, char *arg);

/*
**				frees_functions
*/

void			ft_free_ms_envp(t_mini *ms);
void			ft_free_ms(t_mini *ms);
void			ft_free_line(t_line **line);
void			ft_free_fds(t_mini *ms);
void			ft_free_var(char *aux2, char *aux, char *content);

/*
**				B U I L T   I N S
*/

int				ft_echo(t_mini *ms);
int				ft_pwd(void);
void			ft_env_pwd(t_mini *ms);
int				ft_env(t_mini *ms);
void			ft_no_quotes(t_mini *ms, int j, char type);
int				ft_doer_unset(t_mini *ms, int j);
int				ft_unset(t_mini *ms);
int				ft_pos_equal(char *str);
void			ft_delete(t_mini *ms, int here);

/*
**				FT_EXPORT
*/

int				ft_export(t_mini *ms);
int				ft_doer_export(t_mini *ms, int j);
int				ft_check_equal(char *str);
int				ft_alredy_exists(t_mini *ms, int j);
size_t			ft_strlen_dp(char **s);

int				ft_cd_solo(t_mini *ms, int *ret);
void			ft_exist_doubt(t_mini *ms, int *home_exist, int *save);
int				ft_cd(t_mini *ms);
size_t			ft_strlen_dp(char **s);

/*
** 				CTRL \
*/

void			ft_blocking(int sig);
void			ft_ctrl(int sig);
int				ft_ctrld(char *aux);

/*
**				TERMINAL
*/

t_tcattr		ft_tc_config(void);
void			ft_set_tc(t_tcattr attr, int reset);
void			ft_signals(t_tcattr terminal);
#endif
