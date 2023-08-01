/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvariables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:23:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/28 21:30:14 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    check_and_expand(t_env  *envlist, t_cmd *commandlist)
{
    t_cmd *currentcmd;
    t_env *currentenv;
    char *input;
    char *keytosearch;
    char *temp;
	int i;
    int j;
    int k;
	int end;
	int start;

    currentcmd = commandlist;
	i = 0;
    j = 0;
    while (currentcmd)
    {
        input = ft_strdup(currentcmd->input);
        temp = ft_calloc(100000, 1);
		if (!temp)
			return ;
        while(input[i])
        {
        k = 0;
            while (input[i] && input[i] != '$')
                temp[j++] = input[i++];
            if (input[i] == '$' && (currentcmd->flag_var == 0 || currentcmd->flag_var == 2))
            {
                i = i + 1;
                start = i;
                while (input[i] && ft_isalnum(input[i]))
                    i++;
                end = i - 1;
                keytosearch = ft_substr(input, start, (end - start + 1));
                currentenv = envlist;
                while (currentenv)
                {
                    if (!ft_strcmp(currentenv->key, keytosearch))
                    {
                        while (currentenv->value[k])
                            temp[j++] = currentenv->value[k++];
                        break;
                    }
                    currentenv = currentenv->next;
                }
            i -= 1;
            }
            if (input[i] == '$' && input[i + 1] == '?')
            {
                ft_putstr_fd(ft_itoa(status_exit), 1);
            }
            if (input[i])
                i++;
        }
        temp[j] = '\0';
        currentcmd->input = ft_strdup(temp);
        free(temp);
        i = 0;
        j = 0;
        currentcmd = currentcmd->next;
    }
}
