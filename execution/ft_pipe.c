/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/27 20:20:15 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_pipe(t_shellcmd *cmd, t_env **shellenv)
{
    int    pipfd[2];
    int    pid;
    // int status;

    if (pipe(pipfd) == -1)
    {
        ft_pipe_erreur();
        return ;
    }
    pid = fork();
    if (pid == -1)
    {
        ft_printf("minishell: %e\n", strerror(errno));
        status_exit = 1;
        return ;
    }
    if(cmd->error_flag == 1)
        return;
    if (pid == 0)
    {
        if (cmd->fd_in != -2 && cmd->fd_in != 0)
            dup2(cmd->fd_in,0);
        if (cmd->fd_out != -2 && cmd->fd_out != 1)
            dup2(cmd->fd_out,1);
        close(pipfd[0]);
        dup2(pipfd[1], STDOUT_FILENO);
        close(pipfd[1]);
        pipe_exec_cmd(cmd, shellenv);
        exit(0);
    }
    ft_close_fd(cmd, pipfd);
}

void	ft_close_fd(t_shellcmd *cmd, int pipfd[2])
{
	close(cmd->fd_in);
	close(cmd->fd_out);
	close(pipfd[1]);
	dup2(pipfd[0], STDIN_FILENO);
	close(pipfd[0]);
}

// void	ft_file(t_shellcmd *cmd, int pipfd[2])
// {

// }

void	ft_getpath(t_shellcmd *cmd, t_env **shellenv)
{
	char	*str;
	char	**spl;
	char	*s;
	char	**newenv;

	newenv = ft_envirenment(*shellenv);
	str = git_path(*shellenv);
	if(find(cmd->command[0])== 0)
	{
		ft_creefork(cmd->command[0], cmd, newenv);
		return;
	}
	if (str == NULL)
	{
		ft_putstr_fd(cmd->command[0], 2);
		ft_putstr_fd(" :No such file or directory\n", 2);
		status_exit = 127;
		exit(0);
	}
	spl = ft_split(str, ':');
	s = ft_check_path(spl, cmd->command[0]);
	signal(SIGQUIT, sighandler);
	if (execve(s, cmd->command, newenv) == -1)
	{
		strerror(errno);
		status_exit = 1;
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
