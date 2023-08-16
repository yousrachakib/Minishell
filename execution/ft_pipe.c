/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/16 21:28:53 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pipe(t_shellcmd *cmd, t_env **shellenv)
{
	int	pipfd[2];
	int	pid;

	if (pipe(pipfd) == -1)
	{
		perror("an error with opening the pipe\n");
		status_exit = 1; 
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf("minishell: %e\n", strerror(errno));
		status_exit = 1;
		return ;
	}
	if(cmd->fd_in != -2)
		pipfd[0] = cmd->fd_in;
	if(cmd->fd_out != -2)
		pipfd[1] = cmd->fd_out;
	if (pid == 0)
	{
		close(pipfd[0]);
		dup2(pipfd[1], STDOUT_FILENO);
		close(pipfd[1]);
		pipe_exec_cmd(cmd, shellenv);
		exit(0);
	}
	close(pipfd[1]);
	dup2(pipfd[0], STDIN_FILENO);
	close(pipfd[0]);
}

void	ft_getpath(t_shellcmd *cmd, t_env **shellenv)
{
	char	*str;
	char	**spl;
	char	*s;
	char	**newenv;
	int		i;

	newenv = ft_envirenment(*shellenv);
	i = 0;
	str = git_path(*shellenv);
	if (str == NULL)
	{
		ft_printf("minishell: %e: No such file or directory\n", cmd->command[0]);
		status_exit = 127;
		exit(0);
	}
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[i]);
	signal(SIGQUIT, sighandler);
	execve(s, cmd->command, newenv);
}

void	pipe_exec_cmd(t_shellcmd *cmd, t_env **shellenv)
{
	if(cmd->command && ft_chercher_builtins(cmd, *shellenv) != 0)
		ft_exec_builtins(cmd, shellenv);
	else
		ft_getpath(cmd, shellenv);
}
