/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:49:43 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/27 15:43:15 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void update_shelllvl(t_env **env)
{
	t_env	*tmp;
	int i;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp("SHLVL", tmp->key))
		{
			i = ft_atoi(tmp->value);
			if (i >= 999)
				i = 0;
			else
				i++;
			free(tmp->value);
			tmp->value = ft_itoa(i);
			return ;
		}
		tmp = tmp->next;
	}
}

void	creat_env_struct(char **environment, t_env **env_list)
{
	t_env	*list;
	int		i;

	i = 0;
	list = NULL;
	while (environment[i])
	{
		list = create_envnode(retrieve_key(environment[i]), \
		retrieve_value(environment[i]));
		addback_envnode(env_list, list);
		i++;
	}
	update_shelllvl(env_list);
}
