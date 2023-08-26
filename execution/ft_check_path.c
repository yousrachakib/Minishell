/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/26 14:34:05 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_creefork(char *s, t_shellcmd *cmd, char **newenv)
{
	pid_t	pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Erreur lors de fork()\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(s, cmd->command, newenv) == -1)
		{
			strerror(errno);
			status_exit = 1;
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status_exit =  WEXITSTATUS(status);
	free(s);
	ft_freearr(newenv);
}

void	ft_exec_path(t_shellcmd *cmd, t_env *shellenv )
{
	char	*str;
	char	**spl;
	char	*s;
	char		**newenv;

	newenv = ft_envirenment(shellenv);
	if(find(cmd->command[0])== 0)
	{
		//eccess
		ft_directory(cmd->command[0], cmd, newenv);
		return;
	}
	str = git_path(shellenv);
	if (str == NULL)
	{
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(" :No such file or directory\n", 2);
		status_exit = 127;
		return ;
	}
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[0]);
	if (s == NULL)
		return ;
	ft_creefork(s, cmd, newenv);
	signal(SIGQUIT, sighandler);
	ft_freearr(spl);
	return ;
}

int	find(char *s)
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
