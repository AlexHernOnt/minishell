/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:57:51 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/18 19:06:56 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*aux;
	int		lock;
	t_mini	ms;
	
	lock = 0;
	ft_init(&ms, envp);
	//signal(SIGINT, ft_sighandler);
	while (!lock)
	{
		aux = readline("minishell$");
		if (ft_ctrld(aux, &ms))
			break;
		if (aux[0] != '\0')
		{
			ms.list = ft_parse(aux, &ms);
	//			ft_print_list(&ms);
			if (!ft_organizer(&ms))
				lock = 1;
	//		ft_free_ms(&ms);
			add_history(aux);
		}
		free(aux);
	}
	//rl_clear_history();
	ft_free_ms_envp(&ms);
	return (0);
}

/*
**	Functions that initialize the structs
**	_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
*/

void	ft_init(t_mini *ms, char **envp)
{
	ms->envp = ft_strdup_envp(envp);
	ms->where_was_i = 0;
	ms->red_in = 0;
	ms->red_out = 0;
	ms->pipe = 0;
	ms->pipe_influence = 0;
	ms->o_stdin = dup(0);
	ms->o_stdout = dup(1);
}

char	**ft_strdup_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * ft_strlen_dp(envp) + 1);
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

/*
**	atexit(ft_leaks);
**	rl_on_new_line();
**	rl_replace_line("Bienvenido!", 1);
*/

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
