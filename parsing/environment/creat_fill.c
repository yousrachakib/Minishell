/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:49:43 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/05 17:22:26 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void init_env(t_env *environment)
{
    (environment)->key = NULL;
    (environment)->value = NULL;
}

void    creat_env_struct(char **environment, t_env **final_list)
{
    t_env *list;
    int i;

    i = 0;
    list = NULL;
    while(environment[i])
    {
        puts("hi");
        list = create_envnode(retrieve_key(environment[i]), retrieve_value(environment[i]));
        addback_envnode(final_list, list);
        i++;
    }
    while((*final_list))
    {
        printf("-->>%s", (*final_list)->key);
        printf("-->>%s", (*final_list)->value);
        (*final_list) = (*final_list)->next;
    }
}