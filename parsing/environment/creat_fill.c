/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:49:43 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/24 18:05:01 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    creat_env_struct(char **environment, t_env **final_list)
{
    t_env *list;
    int i;

    i = 0;
    list = NULL;
    while(environment[i])
    {
        list = create_envnode(retrieve_key(environment[i]), retrieve_value(environment[i]));
        addback_envnode(final_list, list);
        i++;
    }
}