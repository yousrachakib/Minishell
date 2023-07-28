/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/28 17:00:07 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(t_shellcmd *cmd , t_env *env)
{
	t_env *current = env;
	int flag = 0;

	while (env)
	{
		if(ft_strncmp(cmd->command[1] ,current->key, ft_strlen(current->key) - 1) == 0)
		{
			free(current->key);
			free(current->value);
			flag = 1;
			if(current->previous != NULL)
				current->previous->next = current->next;
			else
				current = current->next;
			if(current->next != NULL)
				current->next->previous = current->previous;
			free(current);
			return;
		}
		else
			current = current->next;
	}
} 
