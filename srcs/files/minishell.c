#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../minishell.h"

char *readline (const char *prompt);

int main(int argc, char **argv, char **envp)
{
	char	*aux;

	while (1)
	{
		aux = readline("minishell$ ");
		if (aux[0] == 'e' && aux[1] == 'c')
			ft_echo(aux, 0);

		if (aux[0] == 'c' && aux[1] == 'd')
			ft_cd(aux);

		if (aux[0] == 'p' && aux[1] == 'w' && aux[2] == 'd')
			ft_pwd();

		if (aux[0] == 'e' && aux[1] == 'n' && aux[2] == 'v')
			ft_env(envp);

//		rl_on_new_line();
	}
	rl_replace_line("Bienvenido!", 1);

	rl_redisplay();

	return (0);
}
