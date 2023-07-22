/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/21 19:03:50 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_exit(char **cmd)
{
	int i = 0;
	int j = 2;
	if(!cmd[2])
		exit(0);/* indiquer une erreur de commande introuvable.*/
	while(cmd[2][i])
	{
		if(ft_isalpha(cmd[2][i]))
		{
			ft_printf("%e : %e : %e : %e", cmd[0], cmd[1], cmd[2], "numeric argument required");
				exit(255);/*utilisée pour indiquer d'erreur*/
		}
		i++;
	}
	if(!cmd[3])
		exit(ft_atoi(cmd[2]));
	else 
	{
		ft_printf("%e : %e : %e" , cmd[0] , cmd[1],"too many arguments\n");
		return (1);/*utilisée pour indiquer d'erreur*/
	}
	return(0);
}

// int main (int ac, char **av)
// {
// 	ft_exit(av);
// }