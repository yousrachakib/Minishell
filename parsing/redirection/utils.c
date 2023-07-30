/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 21:38:55 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/30 22:10:55 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
int    checkredirection(char c)
{
    if (c == '>' || c == '<')
        return(1);
    return (0);
}

char *copy(char *old)
{
    int i = 0;
    int j = 0;
    char *new;
    new = ft_calloc(ft_strlen(old) + 1, 2);
    while (old[i])
    {
        if (!checkredirection(old[i]))
            new[j] = old[i];
        else
        {
            new[j++] = ' ';
            new[j++] = old[i];
            new[j] = ' ';
        }
        i++;
        j++;
    }
    i = 0;
    while(new[i])
    {
        if( new[i] && new[i+1] && new[i+2] && new[i+3] && checkredirection(new[i]) && checkredirection(new[i + 3]))
        {
            if(new[i + 1])
                i++;
            new[i] = new[i + 2];
            if(new[i + 2])
                i = i + 2;
            new[i] = ' ';
        }
        i++;
    }
    return (new);
}

void set_nonvalidcommand(char **command)
{
    int i ;
    int j;
    char *tmp;
    i = 0;
    while (command[i])
    {
        j = 0;
        while (command[i][j])
        {
            if (checkredirection(command[i][j]))
            {
                tmp = copy(command[i]);
                free(command[i]);
                command[i] = ft_strdup(tmp);
                break;
            }
            j++;  
        }
        i++;
    }
}