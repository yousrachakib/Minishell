/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:02 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/27 14:08:35 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_oldpwd(t_env *env, char *str)
{
	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", 6) == 0)
		{
			// free(env->value);
			env->value = ft_strdup(str);
		}
		env = env->next;
	}
}

void	change_pwd(t_shellcmd *cmd, t_env *env)
{
	char	*str;
	char	pwd[1024];

	(void)cmd;
	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			str = env->value;
			env->value = ft_strdup(getcwd(pwd, sizeof(pwd)));
		}
		env = env->next;
	}
	ft_oldpwd(env, str);
}
