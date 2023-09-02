/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/02 17:04:07 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_path_erreur(char *cmd)
{
	if (access(cmd, F_OK))
	{
		ft_putstr_fd("command not found\n", 2);
		g_j.status_exit = 127;
	}
	else if (access(cmd, X_OK))
	{
		ft_putstr_fd("permission denied\n", 2);
		g_j.status_exit = 126;
	}
}

void	ft_message_erreur(char *s1, char *s2, char *s3, int status)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
	g_j.status_exit = status;
}

void	ft_directory(char *s, t_shellcmd *cmd, char	**newenv)
{
	struct stat	path_stat;

	if (s != NULL && (stat(s, &path_stat) == 0))
		direction(cmd, s, newenv);
	else
	{
		ft_message_erreur("minishell :", cmd->command[0], \
						" :No such file or directorye\n", 127);
		ft_freearr(newenv);
	}
	return ;
}

char	*git_path(t_env *env)
{
	while (env)
	{
		if (env->key && !ft_strncmp(env->key, "PATH", 5))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_stat(char *command, t_shellcmd *cmd, char	**newenv)
{
	if (access(command, X_OK))
	{
		ft_putstr_fd("Minishell :", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(" : permission denied\n", 2);
		g_j.status_exit = 126;
		ft_freearr(newenv);
	}
	else
		ft_creefork(command, cmd, newenv);
}
