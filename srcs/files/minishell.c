/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:57:51 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/22 17:10:54 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *aux;
<<<<<<< HEAD
	t_mini	ms;
	atexit(ft_leaks);

=======
	atexit(ft_leaks);
>>>>>>> 4c52d846ce824434ca9575a5f7fcbd6942d16db0
	ft_init(&ms, envp);
	while (ms.exit == 0)
	{
		g_id = -1;
		signal(SIGINT,ft_ctrlc);
		aux = readline("minishell$ ");
		if (ft_ctrld(aux, &ms))
			break;
		if (aux[0] != '\0' && !ft_only_spaces(aux))
		{
			ms.list = ft_parse(aux, &ms);
<<<<<<< HEAD
		//	ft_print_list(&ms);
			if (ft_organizer(&ms) < 0)
=======
//			ft_print_list(&ms);
			if(ft_organizer(&ms) < 0)
>>>>>>> 4c52d846ce824434ca9575a5f7fcbd6942d16db0
				ms.exit_status = 127;
			ft_free_list(&ms);
			add_history(aux);
		}
		free(aux);
	}
	rl_clear_history();
	ft_free_ms_envp(&ms);
	return (ms.ret);
}
/*
**	Functions that initialize the structs
**	_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*/

void	ft_init(t_mini *ms, char **envp)
{
	ms->envp = ft_strdup_envp(envp);
	ms->ret = 0;
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

char	**ft_strdup_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (ft_strlen_dp(envp) + 1));
	if (new_envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_print_list(t_mini *ms)
{
	t_line  *ptr;

	ptr = ms->list;
	while (ptr != NULL)
	{
		printf("Content: _%s_\t\t : Type %d\n", ptr->content, ptr->type);
		ptr = ptr->next;
	}
	printf("\n");
}


int		ft_only_spaces(char *aux)
{
	while (*aux != '\0')
	{
		if (*aux != ' ' && *aux != '\t')
			return (0);
		aux++;
	}
	return (1);
}
