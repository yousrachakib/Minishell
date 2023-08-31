/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/31 19:22:29 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(t_shellcmd *cmd, t_env **shellenv)
{
	int	pipfd[2];
	int	pid;

	if (pipe(pipfd) == -1)
	{
		ft_pipe_erreur();
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("minishell: %e\n", strerror(errno));
		g_j.status_exit = 1;
		return ;
	}
	if (cmd->error_flag == 1)
		return ;
	if (pid == 0)
	{
		ft_file(cmd, pipfd);
		pipe_exec_cmd(cmd, shellenv);
		exit(0);
	}
	ft_close_fd(cmd, pipfd);
}

char	*pathget(t_shellcmd *cmd, char **newenv, t_env **shellenv)
{
	char	*str;

	str = git_path(*shellenv);
	if (find(cmd->command[0]) == 0)
	{
		ft_creefork(cmd->command[0], cmd, newenv);
		return (NULL);
	}
	if (str == NULL)
	{
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(" :No such file or directory\n", 2);
		g_j.status_exit = 127;
		exit(0);
	}
	return (str);
}

void	ft_getpath(t_shellcmd *cmd, t_env **shellenv)
{
	char	*str;
	char	**spl;
	char	*s;
	char	**newenv;

	newenv = ft_envirenment(*shellenv);
	str = pathget(cmd, newenv, shellenv);
	if (str == NULL)
		return ;
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[0]);
	signal(SIGQUIT, sighandler);
	if (execve(s, cmd->command, newenv) == -1)
	{
		strerror(errno);
		g_j.status_exit = 1;
	}
}



void	pipe_exec_cmd(t_shellcmd *cmd, t_env **shellenv)
{
	if (cmd->command && ft_chercher_builtins(cmd, *shellenv) != 0)
		ft_exec_builtins(cmd, shellenv);
	else
	{
		ft_getpath(cmd, shellenv);
	}
}
