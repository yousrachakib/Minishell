/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/31 19:22:29 by yochakib         ###   ########.fr       */
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
	}
	free(current->key);
	free(current->value);
	free(current);
}

void	ft_unset(t_shellcmd *cmd, t_env **env)
{
	int		j;

	j = 1;
	while (cmd->command[j]) 
	{
		ft_chercher(cmd, env, j);
		j++;
	}
}

void	ft_chercher(t_shellcmd *cmd, t_env **env, int j)
{
	t_env	*curr;
	char	*s;

	if (checkkeyexport(cmd->command[j]) == 0)
	{
		ft_printf("minishell: %e: %e: %e\n", cmd->command[0],
			cmd->command[j], "not a valid identifier");
		g_j.status_exit = 1;
	}
	else
	{
		s = cmd->command[j];
		curr = *env;
		while (curr && ft_strncmp(curr->key, s, ft_strlen(curr->key) + 1))
		{
			if (curr->next == NULL)
				return ;
			curr = curr->next;
		}
		ft_bltunset(curr, env);
	}
}
