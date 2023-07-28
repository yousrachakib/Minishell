/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:35:50 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/28 10:35:44 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int ft_chercher_builtins(t_shellcmd *cmd ,t_env *env)
{
	(void)env;
	int i = 0;
	int len;
	if (cmd)
	{
		len = ft_strlen(cmd->command[0]);
		char *built[8];
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
			if(!ft_strncmp(cmd->command[0] , built[i] , (len + 1)))
				return(1);
			i++;
		}
	}
	return(0);
}
int ft_exec_builtins(t_shellcmd *cmd  , t_env *env)
{
	(void)env;
	if(!ft_strncmp(cmd->command[0] , "echo" , 5))
		ft_echo(cmd);
	if(!ft_strncmp(cmd->command[0] , "cd" , 3))
		ft_cd(cmd ,env);
	if(!ft_strncmp(cmd->command[0] , "export" , 7))
	{
		ft_export(cmd, env); //verifier les cas
		// test_export(cmd, env);
	}
	if(!ft_strncmp(cmd->command[0] , "env" , 5))
		ft_env(env , cmd); 
	if(!ft_strncmp(cmd->command[0], "pwd" , 5))
		ft_pwd();
	if(!ft_strncmp(cmd->command[0] , "unset" , 5))
		ft_unset(cmd, env);//seg
	if(!ft_strncmp(cmd->command[0], "exit" , 5))
		ft_exit(cmd);   
	return(0);
}
int countNodes(t_shellcmd *head) {
    int count = 0;
    t_shellcmd *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
void ft_execution (t_shellcmd *cmd, t_env *shellenv , char **env)
{
	int i;

	i = 0;
	if(!cmd->command[0])
		return ;
	int cnt = countNodes(cmd);
	if(cnt == 1)
	{
		if(cmd->command && ft_chercher_builtins(cmd, shellenv) != 0)
		{
			ft_exec_builtins(cmd , shellenv);
			return ;
		}
		else
			ft_exec_path(cmd, shellenv, env);
	}
	if(cnt > 1)
	{
		// ft_exec_path( cmd->command[i], shellenv, env);
		printf("======");
	}
	return ;
}