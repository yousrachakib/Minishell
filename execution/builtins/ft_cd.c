/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:27:35 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/05 21:25:43 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_path_home(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 5) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (NULL);
}

void	ft_cd(t_shellcmd *cmd, t_env **env)
{
	char	*path_home;
	int		i; 

	if (!cmd->command[1])
		path_home = ft_path_home(*env);
	else
		path_home = ft_strdup(cmd->command[1]);
	i = chdir(path_home);
	if (i < 0)
	{
		ft_printf("minishell: %e: HOME not set\n", cmd->command[0]);
		status_exit = 1;
		return ;
	}
	else
		change_pwd(cmd, *env);
	status_exit = 0;
}
