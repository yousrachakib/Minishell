/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:35:50 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/25 14:36:18 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int ft_chercher_builtins(char *cmd ,t_env *env)
{
	(void)env;
	int i = 0;
	int len;
	if (cmd)
	len = ft_strlen(cmd);
	char *built[8];
	built[0] = "echo";
	built[1] = "cd";
	built[2] = "env";
	built[3] = "exit";
	built[4] = "pwd";
	built[5] = "export";
	built[6] = "unset";
	built[7] = NULL;
	while (built[i] && cmd)
	{
		if(ft_strncmp(cmd , built[i] , (len + 1)))
			return(1);
		i++;
	}
	return(0);
}
int ft_exec_builtins(char **cmd , t_env *env)
{
	if(!ft_strncmp(cmd[1] , "echo" , 5))
		ft_echo(cmd);
	if(!ft_strncmp(cmd[1] , "cd" , 3))
	{
		ft_cd(cmd ,env);
		ft_pwd();
	}
	if(!ft_strncmp(cmd[1] , "export" , 7))
	{
		ft_export(cmd, env); //problem add liste pas terminer
		ft_env(env, cmd[2]);
	}
	if(!ft_strncmp(cmd[1] , "unset" , 5))
	{
		ft_unset(cmd[2], env);
		ft_env(env, cmd[2]);
	}
	if(!ft_strncmp(cmd[1] , "pwd" , 5))
		ft_pwd();
	if(!ft_strncmp(cmd[1] , "env" , 5))
		ft_env(env , cmd[2]); 
	if(!ft_strncmp(cmd[1] , "exit" , 5))
		ft_exit(cmd);   
	return(0);
}
void ft_execution (char **cmd , t_env *env)
{
	int i = 0;
	char *m;
	if(!cmd[1])
		return ;
	if(cmd && ft_chercher_builtins(cmd[1], env))
	{
		ft_exec_builtins(cmd , env);
	}
	ft_exec_path(cmd[1], env);
	return ;
}