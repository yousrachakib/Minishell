/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvariables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:23:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/06 15:58:59 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    check_and_expand(t_env  *envlist, t_cmd *commandlist)
{
    t_cmd *currentcmd;
    t_env *currentenv;
    char *input;
    char *keytosearch;

    currentcmd = commandlist;
    while (currentcmd)
    {
        input = currentcmd->input;
        if (input[0] == '$')
        {
            keytosearch = &input[1];
            currentenv = envlist;
            while (currentenv)
            {
                if (!ft_strcmp(currentenv->key, keytosearch))
                {
                    currentcmd->input = currentenv->value;
                    printf("expanded very well : %s \n", currentcmd->input);
                    break;
                }
                currentenv = currentenv->next;
            }
        }
        currentcmd = currentcmd->next;
    }
}
