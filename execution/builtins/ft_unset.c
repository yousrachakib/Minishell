/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/12 11:04:19 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_bltunset(t_env *current, t_env **env)
{
	if (current)
	{
		if (current == *env) 
		{
			(*env) = current->next;
			if (*env)
				(*env)->previous = NULL;
		}
		else
		{
			if (current->previous)
				current->previous->next = current->next;
		}
		if (current->next)
			current->next->previous = current->previous;
		free(current->key);
		free(current->value);
		free(current);
	}
}

void	ft_unset(t_shellcmd *cmd, t_env **env)
{
	t_env	*current;
	int		j;
	char	*s;

	j = 1;
	while (cmd->command[j]) 
	{
		if (checkkeyexport(cmd->command[j]) == 0)
		{
			ft_printf("minishell: %e: %e: %e\n", cmd->command[0],
				cmd->command[j], "not a valid identifier");
			status_exit = 1;
		}
		else
		{
			s = cmd->command[j];
			current = *env;
			while (current && ft_strncmp(current->key, s, ft_strlen(current->key)))
				current = current->next;
			ft_bltunset(current, env);
		}
		j++;
	}
}

