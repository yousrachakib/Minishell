/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:24:57 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/30 22:50:19 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *here_doc_expand(t_env   *env, char *input)
{
    t_env *currentenv;
    int i;
    int j;
    int k;
    int end;
	int start;
    char *temp;
    char *keytosearch;
    
    temp = ft_calloc(ft_strlen(input) + 1, 10000);
    if (!temp)
        return (NULL);
    i = 0;
    j = 0;
    while(input[i])
    {
        k = 0;
        while (input[i] && input[i] != '$')
            temp[j++] = input[i++];
        if (input[i] == '$')
        {
            i = i + 1;
            start = i;
            while (input[i] && ft_isalnum(input[i]))
                i++;
            end = i - 1;
            keytosearch = ft_substr(input, start, (end - start + 1));
            currentenv = env;
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
    return (temp);
}