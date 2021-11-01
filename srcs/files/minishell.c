/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whoasked <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:08:23 by ahernand          #+#    #+#             */
/*   Updated: 2021/11/01 17:53:05 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_leaks()
{
	system("leaks minishell");
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

int main(int argc, char **argv, char **envp)
{
	char	*aux;
	int		exit;
	t_mini	ms;

	exit = 0;
	ms.envp = ft_strdup_envp(envp);
	while (!exit)
	{
		aux = readline("minishell$ ");
		if (aux[0] == 'e' && aux[1] == 'c')
			ft_echo(aux, 0);
		else if (aux[0] == 'c' && aux[1] == 'd')
			ft_cd(aux);
		else if (aux[0] == 'p' && aux[1] == 'w' && aux[2] == 'd')
			ft_pwd();
		else if (aux[0] == 'e' && aux[1] == 'n' && aux[2] == 'v')
			ft_env(&ms);
		else if (aux[0] == 'e' && aux[1] == 'x' && aux[2] == 'p' && aux[3] == 'o')
			ft_export(&ms, aux);
		else if (aux[0] == 'u' && aux[1] == 'n' && aux[2] == 's' && aux[3] == 'e')
			ft_unset(&ms, aux);
		else if (aux[0] == 'e' && aux[1] == 'x' && aux[2] == 'i' && aux[3] == 't')
			exit = 1;
		else
			if (aux[0] != '\0')
				printf("-minishell: %s: Comand not found\n", aux);

		add_history(aux);
		rl_on_new_line();
	}
	//rl_replace_line("Bienvenido!", 1);

	rl_redisplay();
	return (0);
}
