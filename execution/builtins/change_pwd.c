/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:02 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/06 19:51:45 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_oldpwd(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			str = env->value;
			break ;
		}
		env = env->next;
	}
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "OLDPWD", 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(str);
		}
		tmp = tmp->next;
	}
}

void	change_pwd(t_shellcmd *cmd, t_env *env)
{
	char	*str;
	char	pwd[1024];

	(void)cmd;
	str = NULL;
	ft_oldpwd(env, str);
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			free(env->value);
			env->value = getcwd(g_j.m, sizeof(pwd));
		}
		env = env->next;
	}
}
