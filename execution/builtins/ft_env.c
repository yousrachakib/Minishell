/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:31:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 17:27:41 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_env *env, t_shellcmd *cmd)
{
	if (cmd->command[1])
	{
		ft_printf("%e : %e : %e\n", "env",
			cmd->command[1], "No such file or directory" );
		g_j.status_exit = 127;
		return ;
	}
	while (env)
	{
		if (env->value != NULL && env->value[0] != '\0')
		{
			if (ft_strcmp(env->key, "") == 0 && env->flag_env == 5)
				env = env->next;
			else
				printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return ;
}
