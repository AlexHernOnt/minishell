#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char *prompt);

int main(int argc, char **argv, char **envp)
{
	char	*aux;

	while (1)
	{
		aux = readline("minishell$");
		
		rl_on_new_line();
	}
	rl_replace_line("Bienvenido!", 1);

	rl_redisplay();

	return (0);
}
