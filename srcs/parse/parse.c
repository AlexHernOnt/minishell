/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:32:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/12/22 17:09:03 by ahernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* It returns the length of the first element to be splitted considering quotes 
* rules and trating variables as normal characters. It ignores open quotes
*/

int	get_content_len(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
	{
		if (line[i] == '\'' && ft_check_closed(&line[i], '\''))
			i += ft_quotes(&line[i], '\'');
		if (line[i] == '\"' && ft_check_closed(&line[i], '\"'))
			i += ft_quotes(&line[i], '\"');
		if (i > 0 && (line[i] == '<' || line[i] == '>' || line[i] == '|'))
			return (i);
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			if (line[i + 1] == line[i])
				return (2);
			return (1);
		}
		i++;
	}
	return (i);
}

/* Obtains the type of operators < > and simmilar */

t_line	*ft_more_and_less(t_line *ptr)
{
	if (!ptr->next || ft_is_operator(ptr->next))
		return (ptr);
	if (ptr->content[0] == '<')
	{
		ptr->next->type = 0;
		if (ptr->content[1] == '<')
			ptr->type = 2;
		else if (ptr->content[1] == 0)
			ptr->type = 1;
	}
	if (ptr->content[0] == '>')
	{
		ptr->next->type = 8;
		if (ptr->content[1] == '>')
			ptr->type = 7;
		else if (ptr->content[1] == 0)
			ptr->type = 6;
	}
	return (NULL);
}

/*	Asigns a type to each element of the line
	0 = infile/pwd
	1 = <
	2 = <<
	3 = comand
	4 = argument
	5 = |
	6 = >
	7 = >>
	8 Outfile
*/

/*too long*/
t_line	*ft_get_type(t_line *line)
{
	t_line	*ptr;

	ptr = line;
	while (ptr)
	{
		if (ptr->content[0] == '<' || ptr->content[0] == '>')
			if (ft_more_and_less(ptr))
				return (ft_more_and_less(ptr));
		if (ptr->content[0] == '|')
		{
			if (ft_pipe_sintax(ptr, line))
				return (ptr);
			ptr->type = 5;
		}
		if (ptr->type == -1)
		{
			ptr->type = 3;
			ft_scape_args(ptr);
		}
		else
			ptr = ptr->next;
	}
	return (NULL);
}

/* Reads thee line and separates it in elements of the list conidering
*  exceptions*/

t_line	*ft_get_line(char *line)
{
	int		i;
	int		len;
	char	*tmp;
	t_line	*list_line;

	i = 0;
	list_line = NULL;
	while (line[i])
	{
		if ((i > 0 && line[i - 1]) || i == 0)
		{
			i += ft_ispace(&line[i]);
			len = get_content_len(&line[i]);
			tmp = ft_strdup(&line[i]);
			tmp[len] = 0;
			ft_lineadd_back(&list_line, ft_linenew(ft_strdup(tmp), -1));
			free(tmp);
			i = i + len + ft_ispace(&line[i]);
		}
		else
			break ;
	}
	return (list_line);
}

/* Returns the list separating the line according to shell rules, 
*  expands the variables and assigns a type to each element*/

t_line	*ft_parse(char *line, t_mini *ms)
{
	t_line	*list_line;

	if (!line)
		return (NULL);
	list_line = ft_get_line(line);
	ft_remove_last_space(list_line);
	ft_expansor(list_line, ms);
	if (ft_get_type(list_line))
	{
		if (ft_get_type(list_line)->content[0] == '|')
			ft_error(ms, 258, "|");
		else if (ft_get_type(list_line)->next)
			ft_error(ms, 258, ft_get_type(list_line)->next->content);
		else
			ft_error(ms, 258, "newline");
		ft_free_line(&list_line);
		ms->exit_status = 258;
		return (NULL);
	}
	ft_remove_quotes(list_line);
	return (list_line);
}
