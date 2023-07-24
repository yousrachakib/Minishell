/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:27:35 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/24 11:37:11 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_path_home(t_env *env)
{
	t_env *current;

	current = env;
	
	while (current)
	{
		if(ft_strncmp(current->key, "HOME", 4) == 0)
			return(ft_strdup(current->value));
		current = current->next;
	}
	return(NULL);
}

void ft_cd(char **cmd , t_env *env)
{
	char *path_home;
	int i; 
	
	if(!cmd[2])
		path_home = ft_path_home(env);
	else
		path_home = ft_strdup(cmd[2]);
	i = chdir(path_home);
	if(i < 0)
		ft_printf("%e : %e : %e : %e", "minishell", cmd[1], path_home, "No such file or directory\n");
	else
		change_pwd(cmd , env);
}
