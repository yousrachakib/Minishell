/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/31 21:05:18 by mben-sal         ###   ########.fr       */
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

void ft_creefork(char *s , t_shellcmd *cmd, char **newenv)
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
	{
		ft_printf("minishell: %e\n", "Erreur lors de fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(s, cmd->command,newenv);
	}
	waitpid(pid, NULL,0);
}

void ft_exec_path(t_shellcmd *cmd, t_env *shellenv )
{
	char *str;
	char **spl;
	char *s;
	char **newenv;
	int i;
	
	newenv = ft_envirenment(shellenv);
	i = 0;
	str = git_path(shellenv);
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[i]);
	signal(SIGQUIT,sighandler);
	if(!str)
	{
		ft_printf("minishell: command not found: %e\n", cmd);
		exit(1);
	}
	if (s != NULL)
		ft_creefork(s, cmd, newenv);
	else
		ft_printf("minishell: %e: %e\n", cmd->command[0], "command not found");
}

char *ft_check_path(char **spl, char *cmd)
{
	char	*s;
  
	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			// free (cmd);
			return (cmd);
		}
		else
			return (NULL);
	}
	s = ft_strjoin("/", cmd);
	return(ft_path(spl , s));
}

char	*ft_path(char **spl, char *cmd)
{
	int		i;
	char	*path;

	i = -1;
	while (spl[++i])
	{
		path = ft_strjoin(spl[i], cmd);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	return (NULL);
}
