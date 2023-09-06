/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 12:27:35 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/06 19:41:28 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cas_erreur(void)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	g_j.status_exit = 0;
	return ;
}

char	*ft_path_home(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, "HOME", 5) == 0)
		{
			if (current->value == NULL)
				current->value = ft_strdup("/Users/mben-sal");
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

void	ft_cd(t_shellcmd *cmd, t_env **env)
{
	char	*path_home;
	int		i; 
	char	pwd[1024];

	path_home = ft_home(cmd, env);
	if (!path_home)
		return ;
	i = chdir(path_home);
	if (i < 0)
	{
		perror(cmd->command[1]);
		free(path_home);
		g_j.status_exit = 1;
		return ;
	}
	free(path_home);
	path_home = getcwd(pwd, sizeof(pwd));
	if (!path_home && errno == ENOENT)
	{
		free(path_home);
		return (cas_erreur());
	}
	else
		change_pwd(cmd, *env);
	g_j.status_exit = 0;
}

char	*ft_home(t_shellcmd *cmd, t_env **env)
{
	char	*path_home;

	if (!cmd->command[1]) 
	{
		path_home = ft_path_home(*env);
		if (!path_home) 
		{
			ft_printf("minishell: %e: HOME not set\n", cmd->command[0]);
			free(path_home);
			g_j.status_exit = 1;
			return (NULL);
		}
	}
	else
		path_home = ft_strdup(cmd->command[1]);
	return (path_home);
}
