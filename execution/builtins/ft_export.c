/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 12:08:07 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/23 18:05:07 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	check_key(char *str)
// {
// 	int	i;

// 	if (ft_isdigit(str[0]))
// 		return (0);
// 	else
// 	{
// 		i = -1;
// 		while (str[++i])
// 		{
// 			if (str[i] == '=')
// 				break ;
// 			if (ft_isalnum(str[i]) == 0)
// 				return (0);
// 		}
// 	}
// 	return (1);
// }

// void	printenv(t_var *var)
// {
// 	t_env	*current;

// 	current = var->head_env;
// 	while (current)
// 	{
// 		if (current->key)
// 		{
// 			ft_putstr_fd("declare -x ", 1);
// 			ft_putstr_fd(current->key, 1);
// 			if (ft_strcmp(current->value, "") != 0)
// 			{
// 				ft_putstr_fd("=\"", 1);
// 				ft_putstr_fd(current->value, 1);
// 				ft_putstr_fd("\"", 1);
// 			}
// 			ft_putstr_fd("\n", 1);
// 		}
// 		current = current->next;
// 	}
// }

// void	sub_function_addvar(t_var *var, t_env *current, char **key_value)
// {
// 	while (current)
// 	{
// 		if (ft_strncmp(current->key, key_value[0], \
// 		ft_strlen(key_value[0])) == 0)
// 			break ;
// 		current = current->next;
// 	}
// 	if (current)
// 		current->value = key_value[1];
// 	else
// 	{
// 		current = create_node(key_value);
// 		ft_lstadd_back(&var->head_env, current);
// 	}
// }

// void	addvar_to_export(t_var *var, char **key_value, int i)
// {
// 	t_env	*current;
// 	int		j;

// 	j = 0;
// 	current = var->head_env;
// 	while (var->prs->args[i][j] != '=' && var->prs->args[i][j])
// 		j++;
// 	key_value[0] = ft_substr(var->prs->args[i], 0, j);
// 	if (var->prs->args[i][j] == '=')
// 		key_value[1] = ft_substr(var->prs->args[i], j + 1, \
// 		ft_strlen(var->prs->args[i]) - j);
// 	else
// 		key_value[1] = "";
// 	sub_function_addvar(var, current, key_value);
// 	free (key_value[0]);
// }

// void	ft_export(t_var *var)
// {
// 	char	**key_value;
// 	int		i;

// 	if (!var->prs->args[1])
// 		printenv(var);
// 	i = 0;
// 	while (var->prs->args[++i])
// 	{
// 		if (check_key(var->prs->args[i]) == 0)
// 		{
// 			no_file(var, var->prs->cmd, var->prs->args[i], \
// 			": not a valid identifier\n");
// 		}
// 		else
// 		{
// 			key_value = malloc(sizeof(char) * 3);
// 			key_value[2] = NULL;
// 			addvar_to_export(var, key_value, i);
// 		}
// 	}
// }
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
void ft_export(char **cmd,t_env *env)
{
	t_env *cour = env;
	int i = 1;
	char **key;
	if(!cmd[2])
	{
		print_env(env);
		exit(1);
	}
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
			add_cmd(env, cmd, i, key);
			printf("122");
		}
		i++;
	}
}
void add_cmd(t_env *env , char **cmd , int i , char **key)
{
	t_env *current;
	
	int j = 0;
	current =  env;
	while(cmd[i][j] != '=' && cmd[i][j] !='\0')
		j++;
	key[0] = ft_substr(cmd[i], 0 , j);
	if(cmd[i][j] == '=')
		key[1] = ft_substr(cmd[i], j + 1 , (ft_strlen(cmd[i]) - j));
	else 
		key[1] = "";
	
	
}

// void	sub_function_addvar(t_var *var, t_env *current, char **key_value)
// {
// 	while (current)
// 	{
// 		if (ft_strncmp(current->key, key_value[0], \
// 		ft_strlen(key_value[0])) == 0)
// 			break ;
// 		current = current->next;
// 	}
// 	if (current)
// 		current->value = key_value[1];
// 	else
// 	{
// 		current = create_node(key_value);
// 		ft_lstadd_back(&var->head_env, current);
// 	}
// }