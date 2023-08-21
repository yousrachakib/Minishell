/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:34:10 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/21 13:55:46 by mben-sal         ###   ########.fr       */
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
	int		status;
	t_env	*current;

	current = *shellenv;
	tmp_fd_in = dup(0);
	tmp_fd_out = dup(1);
	if(current == NULL)
		env_null(shellenv);
	while (cmd->next != NULL)
	{
		ft_pipe(cmd, shellenv);
		cmd = cmd->next;
	}
	suite_execution(cmd , shellenv);
	dup2(tmp_fd_in, 0);
	close(tmp_fd_in);
	dup2(tmp_fd_out, 1);
	close(tmp_fd_out);
	while(wait(&status) != -1);
}

void suite_execution(t_shellcmd *cmd, t_env **shellenv)
{
	if(cmd->fd_in != -2)
		dup2(cmd->fd_in, 0);
	if(cmd->fd_out != -2)
		dup2(cmd->fd_out, 1);
	if (cmd->command && ft_chercher_builtins(cmd, *shellenv) != 0)
		ft_exec_builtins(cmd, shellenv);
	else
		ft_exec_path(cmd, *shellenv);
}

void	env_null(t_env **env)
{
	
	t_env	*current; 
	char	*key[0];
	char	*valeur[0];

	current = *env;

	valeur[0] = "";
	key[0] = "";
	current = create_envnode(ft_strdup(key[0]), ft_strdup(valeur[0]));
	addback_envnode(env, current);
	current->flag_env = 5;
	
}

/*parsing*/ 

// seg ===== > ls << asdas

//********//

// dans cette cas (ls < lkj > out et cat < evhvhds)
// if (tmp_list->fd_in == -2 || tmp_list->fd_out == -2)
			//return ;
//*******//
//ajouter dans partier parsing
// main ===> 
// current->hanlder_c = 0;
// signal(SIGINT, handler_c);
// void handler_c(int signo)
// {
// 	t_env var;
// 	(void)signo;
// 	if(!(var.hanlder_c))
// 		return;
// 	if (signo == SIGINT)
// 	{
// 		ft_putstr_fd("\n",1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		status_exit = 1;
// 	}
// }
// changer Makefile 
