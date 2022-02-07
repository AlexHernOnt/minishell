/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:57:51 by ahernand          #+#    #+#             */
/*   Updated: 2022/01/29 11:38:38 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_leaks(void)
{
	system("leaks minishell");
}
//	ft_print_list(ms);
void	ft_reinit(t_mini *ms)
{
	ms->n_in_max = 0;
	ms->red_in = 0;
	ms->red_out = 0;
	ms->append = 0;
}

void	ft_process_line(t_mini *ms, char *aux)
{
	ms->list = ft_parse(aux, ms);
	//ft_print_list(ms);
	if (ms->list)
	{
		if (ft_organizer(ms) < 0)
		{
			ms->exit_status = 127;
		}
		ft_free_list(ms);
	}
	ft_reinit(ms);
}

int	main(int argc, char **argv, char **envp)
{
//	atexit(ft_leaks);
	char	*aux;
	t_mini	ms;

	if (argc < 1 || argv[0] == NULL)
		return (1);
	ft_set_tc();
	ft_init(&ms, envp);
	while (ms.exit == 0)
	{
		g_id = -1;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_ctrl);
		aux = readline("minishell$ ");
		if (ft_ctrld(aux))
			break ;
		if (aux[0] != '\0' && !ft_only_spaces(aux))
		{
			ft_process_line(&ms, aux);
			add_history(aux);
		}
		free(aux);
	}
	rl_clear_history();
	ft_free_ms_envp(&ms);
	return (ms.exit_status);
}

/*
**	Functions that initialize the structs
**	_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*/

void	ft_init(t_mini *ms, char **envp)
{
	ms->envp = ft_strdup_envp(envp);
	ms->exit = 0;
	ms->where_was_i = 0;
	ms->red_in = 0;
	ms->red_out = 0;
	ms->append = 0;
	ms->in_cs = 0;
	ms->in_file = NULL;
	ms->out_file = NULL;
	ms->p_using = 'a';
	ms->pipe = 0;
	ms->n_out_max = 0;
	ms->n_out_cur = 0;
	ms->n_in_max = 0;
	ms->n_in_cur = 0;
	ms->p_first = 1;
	ms->p_last = 0;
	ms->p_done = 0;
	ms->p_b_exists = 0;
	ms->o_stdin = dup(0);
	ms->o_stdout = dup(1);
}
