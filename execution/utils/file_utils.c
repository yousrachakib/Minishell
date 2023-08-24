/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:09:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/21 18:47:00 by mben-sal         ###   ########.fr       */
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
		ft_putstr_fd("permission denied\n", 2);
		status_exit = 126;
	}
}

void	ft_message_erreur(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

void	ft_directory(char *s, t_shellcmd *cmd, t_env *shellenv)
{
	char		**newenv;
	struct stat	path_stat;

	newenv = ft_envirenment(shellenv);
	if (s != NULL && (stat(s, &path_stat) == 0))
	{
		if (S_ISREG(path_stat.st_mode))
			ft_creefork(s, cmd, newenv);
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
}

char	*git_path(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, "PATH", 5))
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

//cuteshell$> ./asads
//command not found