/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:08:07 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/25 14:53:03 by yochakib         ###   ########.fr       */
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
// void ft_check_key(char **cmd, t_env *env)
// {
// 	t_env *current;
// 	current = env;
// 	char *temp;
// 	while(current)
// 	{
// 		if(ft_strncmp(cmd[2], env->key,ft_strlen(cmd[2]))==0)
// 		{
// 			printf("cmd ====> cmd[2] %s" , cmd[2]);
// 			// env->value = 
// 		}
// 		current = current->next;
// 	}
// }
void ft_export(char **cmd,t_env *env)
{
	// t_env *cour = env;
	int i = 2;
	char **key;
	if(!cmd[2])
	{
		print_env(env);
		exit(1);
	}
	// ft_check_key(cmd, env);
	while(cmd[i])
	{
		
		if(ft_check_cmd(cmd[i]) == 0)  
		{
			ft_printf("%e: %e: %e: %e" ,cmd[0] , cmd[1] , cmd[2], "not a valid identifier");
			exit(1);
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
void ajouter_keyvaleur(t_env *env, t_env *courrant , char **cmd, char **key)
{
	while(courrant)
	{
		if(ft_strncmp(courrant->key, cmd[0], ft_strlen(cmd[0])) == 0)
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

// void ft_add_liste(t_env *head, t_env *new_node)
// {
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 	}
// 	else
// 	{
// 		t_env *last = *head;
// 		while (last->next != NULL)
// 		{
// 			last = last->next;
// 		}
// 		last->next = new_node;
// 		new_node->previous = last;
// 	}
// }


void add_cmd(t_env *env , char **cmd , int i , char **key)
{
	t_env *courrant;

	courrant = env;
	int j = 0;
	while(cmd[i][j] != '=' && cmd[i][j] !='\0')
		j++;
	key[0] = ft_substr(cmd[i], 0 , j);
	if(cmd[i][j] == '=')
		key[1] = ft_substr(cmd[i], j + 1 , (ft_strlen(cmd[i]) - j));
	else 
		key[1] = "";
	ajouter_keyvaleur(env ,courrant, cmd, key);
}
int modifier_env(char **key, t_env *env, char **cmd)
{
	int flag = 0;
	int j = 0;
	t_env *current;
	current = env;
	while(cmd[2][j] != '=' && cmd[2][j] !='\0')
		j++;
	key[0] = ft_substr(cmd[2], 0 , j);
	if(cmd[2][j] == '=')
		key[1] = ft_substr(cmd[2], j +1, (ft_strlen(cmd[2]) - j));
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