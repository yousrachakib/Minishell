/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvariables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:23:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/11 19:08:56 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    check_and_expand(t_env  *envlist, t_cmd *commandlist)
{
    t_cmd *currentcmd;
    t_env *currentenv;
    char *input;
    char *keytosearch;
	int i;
	int end;
	int start;

    currentcmd = commandlist;
	i = 0;
    while (currentcmd)
    {
        input = currentcmd->input;
        while (is_whitespace(input[i]))
            i++;
        if (input[i] == '$' && (currentcmd->flag_var == 0 || currentcmd->flag_var == 2))
        {
			i = i + 1;
			start = i;
			while (ft_isalnum(input[i]))
				i++;
			end = i - 1;
			keytosearch = ft_substr(input, start, (end - start + 1));
            currentenv = envlist;
            while (currentenv)
            {
                if (!ft_strcmp(currentenv->key, keytosearch))
                {
                    currentcmd->input = currentenv->value;
                    break;
                }
                // else
                //     currentcmd->input = '\0';
                currentenv = currentenv->next;
            }
        }
		if (input[i] == '$' && input[i + 1] == '?')
		{
			ft_putstr_fd(ft_itoa(status_exit), 1);
		}
        currentcmd = currentcmd->next;
		i++;
    }
}
