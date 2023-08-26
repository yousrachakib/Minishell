/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:49:43 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/26 17:08:49 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	creat_env_struct(char **environment, t_env **final_list)
{
	t_env	*list;
	int		i;

	i = 0;
	list = NULL;
	while (environment[i])
	{
		list = create_envnode(retrieve_key(environment[i]), \
		retrieve_value(environment[i]));
		printf("hi: %p %p\n", list->key, list);
		printf("his: %p %p\n", list->value, list);
		addback_envnode(final_list, list);
		i++;
	}
	
}
