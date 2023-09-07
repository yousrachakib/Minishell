/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:25:02 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/07 19:34:10 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_oldpwd(t_env *env, char *str)
{
	t_env *tmp;

	while (env)
	{
		if (ft_strncmp(env->key, "OLDPWD", 6) == 0)
		{
			env->value = ft_strdup(str);
			return ;
		}
		if (env->next == NULL)
			tmp = env;
		env = env->next;
	}
	addback_envnode(&tmp, create_envnode(ft_strdup("OLDPWD"), ft_strdup(str)));
}

void    change_pwd(t_shellcmd *cmd, t_env *env, char *path)
{
	t_env *trav;
	(void)cmd;

	while (env)
	{
		if (ft_strncmp(env->key, "PWD", 4) == 0)
		{
			free(env->value);
			env->value = ft_strdup(path);
			return ;
		}
		if (env->next == NULL)
			trav = env;
		env = env->next;
	}
	addback_envnode(&trav, create_envnode(ft_strdup("PWD"), ft_strdup(path)));
}
