/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:34:10 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 21:16:40 by mben-sal         ###   ########.fr       */
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
	int		tmp_fd_in;
	int		tmp_fd_out;
	t_env	*current;
	int		i;

	g_j.status_exit = 0;
	i = 0;
	current = *shellenv;
	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	if (current == NULL)
		env_null(shellenv);
	ft_check_k(cmd);
	while (cmd->next != NULL)
	{
		if (ft_pipe(cmd, shellenv))
		{
			cmd->error_flag = 1;
			break ;
		}
		cmd = cmd->next;
	}
	suite_execution(cmd, shellenv);
	dup_close(tmp_fd_in, tmp_fd_out);
}

void	suite_execution(t_shellcmd *cmd, t_env **shellenv)
{
	if (cmd->error_flag == 1)
		return ;
	else
	{
		if (cmd->fd_in != -2)
			dup2(cmd->fd_in, 0);
		if (cmd->fd_out != -2)
			dup2(cmd->fd_out, 1);
	}
	if (cmd->command[0] == NULL)
		return ;
	if (cmd->command && ft_chercher_builtins(cmd, *shellenv) != 0)
		ft_exec_builtins(cmd, shellenv);
	else
		ft_exec_path(cmd, *shellenv);
}

void	env_null(t_env **env)
{
	t_env	*current; 

	current = create_envnode(ft_strdup(""), ft_strdup(""));
	addback_envnode(env, current);
	current->flag_env = 5;
}
