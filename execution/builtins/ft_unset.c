/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/29 10:27:09 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(t_shellcmd *cmd , t_env *env)
{
	t_env *current;
	int j;
	char *s;
	
	j=0;
	while (cmd->command[j])
	{
		s = cmd->command[j];
		current = env;
		while (current && ft_strncmp(current->key, s, ft_strlen(s)))
			current = current->next;
		if(current)
		{
			free(current->key);
			free(current->value);
			current->key = NULL;
			current->value = NULL;
		}
		j++;
	}
} 


// void	ft_unset(t_var *var)
// {
// 	t_env	*current;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (var->prs->args[i])
// 	{
// 		tmp = var->prs->args[i];
// 		current = var->head_env;
// 		while (current && ft_strncmp(current->key, tmp, ft_strlen(tmp)))
// 			current = current->next;
// 		if (current)
// 		{
// 			free(current->key);
// 			free(current->value);
// 			current->key = NULL;
// 			current->value = NULL;
// 		}
// 		i++;
// 	}
// 	var->status = 0;
// }