/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:35:50 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/03 18:45:25 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_chercher_builtins(t_shellcmd *cmd, t_env *env)
{
	int		i;
	int		len;
	char	*built[8];

	i = 0;
	(void)env;
	if (cmd)
	{
		len = ft_strlen(cmd->command[0]);
		built[0] = "echo";
		built[1] = "cd";
		built[2] = "env";
		built[3] = "exit";
		built[4] = "pwd";
		built[5] = "export";
		built[6] = "unset";
		built[7] = NULL;
		while (built[i] && cmd->command[0])
		{
			if (!ft_strncmp(cmd->command[0], built[i], (len + 1)))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_exec_builtins(t_shellcmd *cmd, t_env **env)
{
	(void)env;
	if (!ft_strncmp(cmd->command[0], "echo", 5))
		ft_echo(cmd);
	if (!ft_strncmp(cmd->command[0], "cd", 3))
		ft_cd(cmd, env);
	if (!ft_strncmp(cmd->command[0], "export", 7))
		ft_export(cmd, env);
	if (!ft_strncmp(cmd->command[0], "env", 5))
		ft_env(*env, cmd);
	if (!ft_strncmp(cmd->command[0], "pwd", 5))
		ft_pwd();
	if (!ft_strncmp(cmd->command[0], "unset", 5))
		ft_unset(cmd, env);
	if (!ft_strncmp(cmd->command[0], "exit", 5))
		ft_exit(cmd);
	return (0);
}

void	ft_execution(t_shellcmd *cmd, t_env **shellenv )
{
	int		i;
	int		tmp_fd_in;
	int		tmp_fd_out;

	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	i = 0;
	if (!cmd->command[0])
		return ;
	while (cmd->next)
	{
		ft_pipe(cmd, shellenv);
		cmd = cmd->next;
	}
	dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->command && ft_chercher_builtins(cmd, *shellenv) != 0)
		ft_exec_builtins(cmd, shellenv);
	else
		ft_exec_path(cmd, *shellenv);
	dup2(tmp_fd_in, 0);
	close(tmp_fd_in);
	dup2(tmp_fd_out, 1);
	close(tmp_fd_out);
}
