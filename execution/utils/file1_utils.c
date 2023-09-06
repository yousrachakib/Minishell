/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:23:48 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 16:59:08 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exit_child(int status)
{
	if (WIFSTOPPED(status))
		return (128 + WSTOPSIG(status));
	if (WIFSIGNALED(status))
	{
		printf("\n");
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
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

void	ft_file(t_shellcmd *cmd, int pipfd[2])
{
	close(pipfd[0]);
	dup2(pipfd[1], STDOUT_FILENO);
	close(pipfd[1]);
	if (cmd->fd_in != -2 && cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != -2 && cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
}

void	ft_close_fd(t_shellcmd *cmd, int pipfd[2])
{
	close(cmd->fd_in);
	close(cmd->fd_out);
	close(pipfd[1]);
	dup2(pipfd[0], STDIN_FILENO);
	close(pipfd[0]);
}

void	direction(t_shellcmd *cmd, char *s, char **newenv)
{
	struct stat	path_stat;

	if (s != NULL && (stat(s, &path_stat) == 0))
	{
		if (S_ISREG(path_stat.st_mode))
		{
			ft_stat(cmd->command[0], cmd, newenv);
			return ;
		}
		else if (S_ISDIR(path_stat.st_mode))
		{
			ft_message_erreur ("minishell :", s, " :Is a directory\n", 126);
			ft_freearr(newenv);
		}
		else
		{
			ft_message_erreur("minishell :", s,
				" :Not an executable file\n", 127);
			ft_freearr(newenv);
		}
	}
}
