/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:08:23 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/11 18:21:08 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_ms(t_mini *ms)
{
	int	i;

	i = 0;
	if (ms->cmd)
		free(ms->cmd);
	while (ms->args[i] != NULL)
	{
		if (ms->args[i])
			free(ms->args[i]);
		i++;
	}
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

int	main(int argc, char **argv, char **envp)
{
	char	*aux;
	t_mini	ms;

	ms.envp = ft_strdup_envp(envp);
	while (1)
	{
		aux = readline("minishell$ ");
		ms.list = ft_parse(aux, &ms);
//		ft_print_list(&ms);

		ft_organizer(&ms);
		ft_free_ms(&ms);
		add_history(aux);
		free(aux);
	}
	rl_clear_history();
	ft_free_ms_envp(&ms);
	return (0);
}

/*
**	E N V
**	_ _ _
*/

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
//	atexit(ft_leaks);
//	rl_on_new_line();
//	rl_replace_line("Bienvenido!", 1);
