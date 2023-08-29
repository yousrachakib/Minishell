/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/29 20:48:59 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_path_erreur(char *cmd)
{
	if (access(cmd, F_OK))
	{
		ft_putstr_fd("command not found\n", 2);
		status_exit = 127;
	}
	else if (access(cmd, X_OK))
	{
		ft_putstr_fd("Minishell :", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" : permission!! denied\n", 2);
		status_exit = 126;
		return;
	}
}

void	ft_message_erreur(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

void	ft_directory(char *s, t_shellcmd *cmd, char	**newenv)
{
	struct stat	path_stat;

	if (s != NULL && (stat(s, &path_stat) == 0))
	{
		if (S_ISREG(path_stat.st_mode))
		{
			ft_path_erreur(cmd->command[0]);
			ft_creefork(cmd->command[0], cmd, newenv);
				return;
		}
		else if (S_ISDIR(path_stat.st_mode))
		{
			ft_message_erreur ("minishell :", s, " :Is a directory\n");
			status_exit = 126;
		}
		else
		{
			ft_message_erreur("minishell :", s, " :Not an executable file\n" );
			status_exit = 127;
		}
	}
	else
	{
		ft_message_erreur("minishell :", cmd->command[0], \
						" :No such file or directorye\n" );
		status_exit = 127;
	}
	return;
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

