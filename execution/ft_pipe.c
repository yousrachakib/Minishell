/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/01 19:20:04 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pipe(t_shellcmd *cmd, t_env **shellenv)
{
	int pipfd[2];
	int pid;

	if(pipe(pipfd) == -1)
	{
		perror("an error with opening the pipe\n");
		return;
	}
	pid = fork();
	if (pid == -1) {
		ft_printf("minishell: %e\n", strerror(errno));
		return ;
	}
	if(pid == 0)
	{
		close(pipfd[0]);
		dup2(pipfd[1], 1);
		close(pipfd[1]);
		if(ft_exec_builtins(cmd , shellenv))
			return ;
		ft_getpath(cmd , shellenv);
	}
	close(pipfd[1]);
	dup2(pipfd[0],STDIN_FILENO);
	close(pipfd[0]);
}

void ft_getpath(t_shellcmd *cmd , t_env **shellenv)
{
	char *str;
	char **spl;
	char *s;
	char **newenv;
	int i;
	
	newenv = ft_envirenment(*shellenv);
	i = 0;
	str = git_path(*shellenv);
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[i]);
	signal(SIGQUIT, sighandler);
	if(!str)
	{
		ft_printf("minishell: command not found: %e\n", cmd);
		exit(1);
	}
	execve(s, cmd->command, newenv);
	ft_printf("minishell: %e: %e\n", cmd->command[0], "command not found");
}