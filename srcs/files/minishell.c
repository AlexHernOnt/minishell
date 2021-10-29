#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../minishell.h"

char *readline (const char *prompt);

int main(int argc, char **argv, char **envp)
{
	char	*aux;
	int		exit;

	exit = 0;
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
			ft_env(envp);
		else if (aux[0] == 'e' && aux[1] == 'x' && aux[2] == 'p' && aux[3] == 'o')
			ft_export(aux, envp);
//		else if (aux[0] == 'u' && aux[1] == 'n' && aux[2] == 's' && aux[3] == 'e')
//			ft_unset(envp);
		else if (aux[0] == 'e' && aux[1] == 'x' && aux[2] == 'i' && aux[3] == 't')
			exit = 1;
		else
			printf("-minishell: %s: Comand not found\n", aux);
		add_history(aux);
		rl_on_new_line();
	}
	//rl_replace_line("Bienvenido!", 1);

	rl_redisplay();
	return (0);
}
