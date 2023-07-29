/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:28:15 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/29 11:01:05 by mben-sal         ###   ########.fr       */
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

void sighandler(int sig)
{
	(void)sig;
	printf("^\\Quit:\n");
}
int countNodes(t_env *head) {
    int count = 0;
    t_env *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
char **ft_envirenment(t_env *shellenv)
{
	int cnt;
	int i;
	char **env;
	char *key;
	
	i = 0;
	cnt = countNodes(shellenv) + 1;
	env = (char **)malloc(cnt * sizeof(char*));
	i = 0;
	while (shellenv->next != NULL && i < cnt)
	{
		key = ft_strjoin(shellenv->key, "=");
		env[i] = ft_strjoin(key , shellenv->value);
		free(key);
		i++;
		shellenv = shellenv->next;
	}
	return(env);
}
void ft_exec_path(t_shellcmd *cmd, t_env *shellenv , char **env)
{
	(void)env;
	char *str = git_path(shellenv);
	char **spl;
	char *s;
	char **newenv;
	

	newenv = ft_envirenment(shellenv);
	int i = 0;
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[i]);
	signal(SIGQUIT,sighandler);
	if(!str)
	{
		ft_printf("minishell: command not found: %e\n", cmd);
		exit(1);
	}
	if (s != NULL)
	{
		pid_t pid = fork();
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
	else
		ft_printf("minishell: %e: %e\n", cmd->command[0], "command not found");
}

char *ft_check_path(char **spl, char *cmd)
{
	char	*s;
	// char	**str;
  
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
