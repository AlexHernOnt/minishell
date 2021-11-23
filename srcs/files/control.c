/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorion- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 09:25:17 by amorion-          #+#    #+#             */
/*   Updated: 2021/11/21 09:25:20 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* Si hay ctl-d libera aux y retorna 1 para salir del bucle después*/
int ft_ctrld(char *aux, t_mini *ms)
{
    if (!aux)
    {
        printf("\n");
        free(aux);
        return (1);
    }
    return (0);
}

void ft_sighandler(int sig)
{
    printf("\n");
    exit(0);
}
void ft_sigempty(int sig)
{
    //printf("Cosas\n");
    rl_on_new_line();
    rl_replace_line("minishell$", 0);
    rl_redisplay();
}