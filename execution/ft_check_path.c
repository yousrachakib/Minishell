/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/16 21:01:28 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_creefork(char *s, t_shellcmd *cmd, char **newenv)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_printf("minishell: %e\n", "Erreur lors de fork()");
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
	char	**newenv;
	int		i;

	newenv = ft_envirenment(shellenv);
	i = 0;
	str = git_path(shellenv);
	if (str == NULL)
	{
		ft_printf("minishell: %e: No such file or directory\n", cmd->command[0]);
		ft_freearr(newenv);
		status_exit = 127;
		return ;
	}
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[i]);
	signal(SIGQUIT, sighandler);
	ft_freearr(spl);
	if (s != NULL)
		ft_creefork(s, cmd, newenv);
	else
	{
		ft_freearr(newenv);
		return ;
	}
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
			if (access(cmd, F_OK))
			{
				ft_putstr_fd(" command not found\n", 2);
				status_exit = 127;
			}
			else if (access(cmd, X_OK))
			{
				ft_putstr_fd("permission denied\n", 2);
				status_exit = 126;
			}
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
				ft_printf("%e permission denied\n", cmd + 1);
				status_exit = 126;
				free(cmd);
				free(path);
				return (NULL);
			}
		}
		free(path);
	}
	ft_printf("%e command not found\n", cmd + 1);
	status_exit = 127;
	return (NULL);
}
// ls | a| b | c | ls
// bash: a: command not found
// bash: b: command not found
// bash: c: command not found