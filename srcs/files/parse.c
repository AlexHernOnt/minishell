/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:32:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/10/28 16:32:19 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_line	*ft_linenew(void *content, int type)
{
	t_line	*nl;

	nl = malloc(sizeof(t_list));
	if (!nl)
		return (NULL);
	nl->content = content;
	nl->type = type;
	nl->next = NULL;
	return (nl);
}

int get_content_len(char *line)
{
	int i;

	i = 0;
	while(line[i] && line[i] != ' ' && line[i] !='\t')
	{
		/*if(line[i] = '\'' && ft_check_closed(&line[i], '\''))
			i += ft_simple_quote(line);
		if(line[i] = '\"' && ft_check_closed(&line[i], '\"'))
			i += ft_double_quote(line);*/
		if(i > 0 && (line[i] == '$' || line[i] == '<' || line[i] == '>' || line[i] == '|'))
			return(i);
		/*else if (line[i] == '$')
			return(ft_variable(line));*/
		else if (line[i] == '<')
		{
			if (line[i++] == '<')
				return(2);
			return(1);
		}
		else if (line[i] == '>')
		{
			if (line[i++] = '>')
				return(2);
			return(1);
		}
		i++;
	}
	return(i);
}

ft_get_type(char *line)
{
	(void)line;
	return(0);
}

t_list  *ft_parse(char *line)
{
	t_line *list_line;
	int len;
	char *tmp;

	list_line = NULL;
	while(*line)
	{
		len = get_content_len(line);
		tmp = strdup(line);
		tmp[len]=0;
		ft_lstadd_back(list_line, ft_linenew(strdup(tmp), ft_get_type(line)));
		free(tmp);
		line += len + 1;
	}
	return(list_line);
}

int main(int agrc, char **argv)
{
	t_line *list;

	list = ft_parse(argv[1]);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
	return(0);
}