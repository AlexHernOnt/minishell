/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 16:57:51 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/15 18:56:59 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*aux;
	t_mini	ms;

	ft_init(&ms, envp);
	while (1)
	{
		aux = readline("minishell$ ");
		if (aux[0] != '\0')
		{
			ms.list = ft_parse(aux, &ms);
//			ft_print_list(&ms);
			if (!ft_organizer(&ms))
			{
				ft_free_ms(&ms);
				add_history(aux);
				return(0);
			}
			ft_free_ms(&ms);
			add_history(aux);
		}
		free(aux);
	}
	rl_clear_history();
	ft_free_ms_envp(&ms);
	return (0);
}

/*
**	I N I T
**	_ _ _ _
*/

void	ft_init(t_mini *ms, char **envp)
{
	ms->envp = ft_strdup_envp(envp);
	ms->red_out = 0;
	ms->o_stdin = dup(1);
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
