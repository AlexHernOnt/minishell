/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahernand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:30:24 by ahernand          #+#    #+#             */
/*   Updated: 2021/12/28 16:48:46 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_list(t_mini *ms)
{
	t_line	*ptr;

	ptr = ms->list;
	while (ptr != NULL)
	{
		printf("Content: _%s_\t\t : Type %d\n", ptr->content, ptr->type);
		ptr = ptr->next;
	}
	printf("\n");
}

int	ft_error(t_mini *ms, int code, char *arg)
{
	dup2(2, 1);
	if (code == 1)
	{
		printf("-minishell: %s: too many arguments\n", arg);
		return (1);
	}
	if (code == 101)
		printf("-minishell: unset: `%s': not a valid identifier\n", arg);
	if (code == 102)
		printf("-minishell: export: `%s': not a valid identifier\n", arg);
	if (code == 105)
		printf("Pipe failed\n");
	if (code == 201)
		printf("-minishell: %s: No such file or directory\n", arg);
	if (code == 23)
	{
		printf("-minishell: %s: Command not found\n", arg);
		return (127);
	}
	if (code == 255)
	{
		printf("-minishell: exit: %s: numeric argument required\n", arg);
		return (255);
	}
	if (code == 258)
		printf("-minishell: syntax error near unexpected token `%s\'\n", arg);
	dup2(ms->o_stdout, 1);
	return (-1);
}
