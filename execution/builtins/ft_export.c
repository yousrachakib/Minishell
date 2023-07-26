/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:08:07 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/26 12:04:04 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_env *env)
{

	while (env)
	{
		if (env->key)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->key, 1);
			if (ft_strcmp(env->value, "") != 0)
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}
int ft_check_cmd(char *str)
{
	int i = 0;
	if(ft_isdigit(str[0]))
		return(0);
	else 
	{
		while (str[i])
		{
			if(str[i] == '=')
				break;
			i++;
		}
		
	}
	return(1);
}

void ft_export(t_shellcmd *cmd,t_env *env)
{
	int i = 1;
	char **key;
	if(!cmd->command[1])
	{
		print_env(env);
		return ;
	}
	while(cmd->command[i])
	{
		if(ft_check_cmd(cmd->command[i]) == 0)  
		{
			ft_printf("%e: %e: %e\n" ,cmd->command[0] , cmd->command[1] , "not a valid identifier");
			return ;
		}
		else
		{
			key = malloc(sizeof(char) * 3);
			key[2] = NULL;
			if(modifier_env(key,env,cmd) != 0)
				add_cmd(env, cmd, i, key);
			else
				modifier_env(key,env,cmd);
		}
		i++;
	}
}
void ajouter_keyvaleur(t_env *env, t_env *courrant , t_shellcmd *cmd, char **key)
{
	while(courrant)
	{
		if(ft_strncmp(courrant->key, cmd->command[1], ft_strlen(cmd->command[1])) == 0)
			break;
		courrant = courrant->next;
	}
	if(courrant)
		courrant->value = key[1];
	else
	{
		courrant = create_envnode(key[0], key[1]);
		addback_envnode(&env , courrant);
	}
}

void add_cmd(t_env *env , t_shellcmd *cmd , int i , char **key)
{
	t_env *courrant;

	courrant = env;
	int j = 0;
	while(cmd->command[i][j] != '=' && cmd->command[i][j] !='\0')
		j++;
	key[0] = ft_substr(cmd->command[i], 0 , j);
	if(cmd->command[i][j] == '=')
		key[1] = ft_substr(cmd->command[i], j + 1 , (ft_strlen(cmd->command[i]) - j));
	else 
		key[1] = "";
	ajouter_keyvaleur(env ,courrant, cmd, key);
}
int modifier_env(char **key, t_env *env, t_shellcmd *cmd)
{
	int flag = 0;
	int j = 0;
	t_env *current;
	current = env;
	while(cmd->command[1][j]!= '=' && cmd->command[1][j] !='\0')
		j++;
	key[0] = ft_substr(cmd->command[1], 0 , j);
	if(cmd->command[1][j] == '=')
		key[1] = ft_substr(cmd->command[1], j + 1, (ft_strlen(cmd->command[1]) - j));
	j = 0;
	while (current)
	{
		if(!ft_strncmp(key[0],current->key, ft_strlen(key[0])))
		{
			current->value = key[1];
			flag = 1;
		}
		current = current->next;
	}
	if(flag)
		return(0);
	return(1);
}