/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:02 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 18:40:07 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_oldpwd(t_env *env, char *str)
{
	t_env	*tmp_env;
	t_env	*current;

	tmp_env = env;
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", 6) == 0)
		{
			free(env->value);
			env->value = ft_strdup(str);
			break;
		}
		env = env->next;
	}
	if (!env)
	{
		current = create_envnode(ft_strdup("OLDPWD"), ft_strdup(str));
		addback_envnode(&tmp_env, current);
		return ;
	}
}

void	change_pwd(t_shellcmd *cmd, t_env *env)
{
	char	*str;
	t_env	*tmp_env;
	t_env	*current;
	char	pwd[1024];

	(void)cmd;
	tmp_env = env;
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			str = env->value;
			free(env->value);
			env->value = ft_strdup(getcwd(pwd, sizeof(pwd)));
			break;
		}
		env = env->next;
	}
	if (!env)
	{
		current = create_envnode(ft_strdup("PWD"), ft_strdup(getcwd(pwd, sizeof(pwd))));
		addback_envnode(&tmp_env, current);
		return ;
	}
	env = tmp_env;
	ft_oldpwd(env, str);
}
