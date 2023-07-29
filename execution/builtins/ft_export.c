/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:08:07 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/29 18:37:45 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key)
		{
			if (env->key != NULL && env->key[0] != '\0')
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(env->key, 1);
				if (env->value != NULL && env->value[0] != '\0')
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(env->value, 1);
					ft_putstr_fd("\"", 1);
				}
				ft_putstr_fd("\n", 1);
			}
		}
		env = env->next;
	}
}

int checkKeyExport(char* str) 
{
	int i = 1;
    if (!ft_isalpha(str[0]) && str[0] != '_') {
		printf("here\n");
        return 0;
    }
    while( str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return 1;
	    if (ft_isalnum(str[i]) == 0)
			return 0;
		i++;
	}
    return 1;
}

void ft_export(t_shellcmd *cmd,t_env **env)
{
	int i = 1;
	if(!cmd->command[1])
	{
		print_env(*env);
		return ;
	}
	while(cmd->command[i])
	{
		if(checkKeyExport(cmd->command[i]) == 0)
			ft_printf("%e: %e: %e\n" ,cmd->command[0] , cmd->command[i], "not a valid identifier");
		else
			modifier_env(env, cmd->command[i]);
		i++;
	}
}

void ajouter_keyvaleur(t_env *env , char *str, char **key)
{
	t_env *courrant = env;

	while(courrant)
	{
		if(ft_strncmp(courrant->key, str, ft_strlen(str) + 1) == 0)
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

int modifier_env(t_env **env, char *command)
{
	int flag = 0;
	int j = 0;
	t_env *current;
	char **key;
	current = *env;
	while(command[j] !='\0')
	{
		if ((command[j] == '+' && command[j + 1] == '=') || command[j] == '=')
		{
			if(command[j] == '+')
				flag = 2;
			break ;
		}
		j++;
	}
	key = malloc(sizeof(char) * 3);
	if (!key)
		return 0;
	key[2] = NULL;
	if (flag == 2) {	
		key[0] = ft_substr(command, 0, j);
		key[1] = ft_substr(command, j + 2, (ft_strlen(command) - j));
	}
	else if (flag != 2)
		key[0] = ft_substr(command, 0 , j);
	if (command[j] == '=' && flag != 2)
		key[1] = ft_substr(command, j + 1, (ft_strlen(command) - j));
	if (command[j] == '\0' && command[j] == '=') {
		key[1] = ft_strdup("");
	}
	else if (command[j] == '\0')
	{
		key[1] = NULL;
		flag = 0;
	}
	if(ft_change_env(key , current , flag) == 1)
		return(0);
	ajouter_keyvaleur(*env, command, key);
	return(1);
}

int ft_change_env(char **key , t_env *current , int flag)
{
	while (current)
	{
		if(!ft_strncmp(key[0],current->key, ft_strlen(key[0]) + 1))
		{
			if(flag == 2 && key[1])
			{
				if (current->value == NULL)
					current->value = ft_strdup("");
				current->value = ft_strjoin(current->value, key[1]);
			}
			else
				current->value = key[1];
			flag = 1;
		}
		current = current->next;
	}
	return(flag);
}
