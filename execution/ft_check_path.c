/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/24 21:26:39 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_creefork(char *s, t_shellcmd *cmd, char **newenv)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Erreur lors de fork()\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(s, cmd->command, newenv);
	}
	waitpid(pid, NULL, 0);
	free(s);
	ft_freearr(newenv);
}

void	ft_exec_path(t_shellcmd *cmd, t_env *shellenv )
{
	char	*str;
	char	**spl;
	char	*s;

	str = git_path(shellenv);
	if (str == NULL)
	{
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd("No such file or directory\n", 2);
		status_exit = 127;
		return ;
	}
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[0]);
	if (s == NULL)
		return ;
	signal(SIGQUIT, sighandler);
	ft_freearr(spl);
	ft_directory(s, cmd, shellenv);
	return ;
}

static int	find(char *s)
{
	while (*s)
	{
		if (*s == '/')
			return (0);
		s++;
	}
	return (1);
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
	s = ft_strjoin("/", cmd);
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
	while (spl[++i])
	{
		path = ft_strjoin(spl[i], cmd);
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
	ft_message_erreur("minishell :", cmd + 1, " :command not found \n");
	status_exit = 127;
	return (NULL);
}
