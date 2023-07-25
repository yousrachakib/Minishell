/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:31:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/25 17:13:01 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env (t_env *env , char *cmd)
{
	(void)cmd;
	// int i = 0;
	// char **str = env;
	
	// if(cmd)
	// {
		// ft_printf("%e : %e : %e" , "env" , cmd , "No such file or directory" );
	// 	// ft_free(str);
	// 	return(1);
	// }
	// while (str && str[i])
	// {
	// 	ft_putstr_fd(str[i] , 1);
	// 	ft_putstr_fd("\n", 1);
	// 	i++;
	// }
		// printf("test %s\n", env->key);
	while(env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
	exit(1);
}
// int main(int ac , char **av , char **env)
// {
// 	char *cur = getenv("PWD");
// 	printf("Répertoire de travail actuel (PWD) : %s\n", cur);
// 	char *str = av[2];
// 	ft_env(env , str);
	
// 	return(0);
// }