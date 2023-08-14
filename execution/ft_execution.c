/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:35:50 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/14 10:30:24 by mben-sal         ###   ########.fr       */
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
	int		status;
	t_env	*current;

	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	i = 0;
	current = *shellenv;
	if(current == NULL)
		env_null(shellenv);
	while (cmd->next != NULL)
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
	while(wait(&status) != -1);
}

void	env_null(t_env **env)
{
	int j;
	t_env *current; 
	char *key[6];
	char *valeur[6];

	current = *env;
	j = 0;
	valeur[0]="/Users/mben-sal/Desktop/Cursus/minishell";
	valeur[1]="1";
	valeur[2]="/usr/bin/env";
	valeur[3]="/Users/mben-sal/.brew/bin:/Users/mben-sal/brew/bin:/Users/mben-sal/.brew/bin:/Users/mben-sal/goinfre/homebrew/bin:/Users/mben-sal/goinfre/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	valeur[4]= "/Users/mben-sal";
	valeur[5]=NULL;
	key[0] = "PWD";
	key[1] = "SHLVL";
	key[2] = "_";
	key[3] = "PATH";
	key[4] = "HOME";
	key[5] = NULL;
	while(j <= 5)
	{
		current = create_envnode(key[j], valeur[j]);
		addback_envnode(env, current);
		current->flag_env = 5;
		j++;
	}
	
}	
	