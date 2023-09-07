/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/07 19:27:46 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_creefork(char *s, t_shellcmd *cmd, char **newenv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Erreur lors de fork()\n", 2);
		g_j.status_exit = 1;
		return ;
	}
	else if (pid == 0)
	{
		if (execve(s, cmd->command, newenv) == -1)
		{
			strerror(errno);
			g_j.status_exit = 1;
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	g_j.status_exit = exit_child(status);
	ft_freearr(newenv);
}

void	ft_exec_path(t_shellcmd *cmd, t_env *shellenv )
{
	char	*str;
	char	**spl;
	char	*s;
	char	**newenv;

	newenv = ft_envirenment(shellenv);
	str = ft_direction(cmd, newenv, shellenv);
	if (str == NULL)
		return ;
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[0]);
	if (s == NULL)
	{
		ft_freearr(newenv);
		ft_freearr(spl);
		return ;
	}
	ft_creefork(s, cmd, newenv);
	free (s);
	signal(SIGQUIT, sighandler);
	ft_freearr(spl);
	return ;
}

char	*ft_direction(t_shellcmd *cmd, char **newenv, t_env *shellenv)
{
	char	*str;

	if (find(cmd->command[0]) == 0)
	{
		ft_directory(cmd->command[0], cmd, newenv);
		return (NULL);
	}
	str = git_path(shellenv);
	if (str == NULL)
	{
		ft_message_erreur ("minishell :", cmd->command[0], \
			" :No such file or directory \n", 127);
		ft_freearr(newenv);
		return (NULL);
	}
	return (str);
}

char	*ft_check_path(char **spl, char *cmd)
{
	char	*s;
	char	*path;

	if (find(cmd) == 0)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		else
		{
			ft_path_erreur(cmd);
			return (NULL);
		}
	}
	s = my_strjoin("/", cmd);
	path = ft_path(spl, s);
	if (path == NULL)
		free(s);
	return (path);
}

char	*ft_path(char **spl, char *cmd)
{
	int		i;
	char	*path;

	i = -1;
	while (spl[++i] && cmd[1])
	{
		path = my_strjoin(spl[i], cmd);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0) 
			{
				free(cmd);
				return (path);
			}
			else
			{
				ft_erreur_access(path, cmd);
				return (NULL);
			}
		}
		free(path);
	}
	ft_message_erreur("minishell :", cmd + 1, " :command not found \n", 127);
	return (NULL);
}
