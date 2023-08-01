/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/25 17:13:28 by mben-sal         ###   ########.fr       */
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

void ft_exec_path(char *cmd, t_env *env)
{
	char *str = git_path(env);
	char **spl;
	char *s;
	char **exec_arg;
	// pid_t pid = fork();
	if(!str)
	{
		ft_printf("minishell: command not found: %e\n", cmd);
		exit(1);
	}
	spl = ft_split(str, ':');
	exec_arg = ft_split(cmd ,' ');
	s = ft_check_path(spl, cmd);//probleme d etulise execve
	// if(s != NULL)
	// {
	// 	if(pid == -1)
	// 	{
	// 		ft_printf("minishell: %e\n", "Erreur lors de fork()");
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	else if (pid == 0)
	// 		execve(s,exec_arg,env);
	// 	else
	// 		waitpid(pid, NULL,0);
	// }
}

char *ft_check_path(char **spl, char *cmd)
{
	char	*s;
	// char	**str;
  
	if (ft_strncmp(cmd, "/", 1) == 0)
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			free (cmd);
			return (cmd);
		}
		ft_printf("minishell: %e: %e\n", "command not found", cmd);
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
