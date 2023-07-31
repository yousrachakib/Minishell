/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:08:22 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/31 20:47:12 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void ft_pipe(t_shellcmd *cmd,t_env **shellenv)
// {
// 	int pipfd[2];
// 	int pid;
	
// 	if(pipe(pipfd) == -1)
// 	{
// 		perror("an error with opening the pipe\n");
// 		return;
// 	}
// 	dup2(pipfd[1],STDOUT_FILENO);
// 	pid =fork();
// 	if (pid == -1) {
// 		ft_printf("minishell: %e\n", strerror(errno));
// 		return ;
// 	}
// 	if(pid == 0)
// 	{
// 		if(ft_exec_builtins(cmd , shellenv))
// 			exit(0);
// 		ft_exec_path(cmd, *shellenv);
// 	}
// }
