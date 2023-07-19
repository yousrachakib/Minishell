/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:31:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/19 19:06:59 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_env (char **env , char *cmd)
{
	int i = 0;
	char **str = env;
	
	if(cmd)
	{
		ft_printf("%e : %e : %e" , "env" , cmd , "No such file or directory" );
		// ft_free(str);
		exit(1);
	}
	while (str && str[i])
	{
		ft_putstr_fd(str[i] , 1);
		ft_putstr_fd("\n", 1);
		
		i++;
	}
	return(0);
}
int main(int ac , char **av , char **env)
{
	char *str = av[2];
	ft_env(env , str);
	return(0);
}