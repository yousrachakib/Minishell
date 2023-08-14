/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/01 21:01:28 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_shellcmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd->command[1])
		exit (0);/* indiquer une erreur de commande introuvable.*/
	while (cmd->command[1][i])
	{
		if (ft_isalpha(cmd->command[1][i]))
		{
			ft_printf("%e :%e : %e : %e", "minishell", cmd->command[0],
				cmd->command[1], "numeric argument required");
			exit (255);/*utilisée pour indiquer d'erreur*/
		}
		i++;
	}
	if (!cmd->command[2])
		exit (ft_atoi(cmd->command[1]));
	else 
	{
		ft_printf("%e :%e : %e : %e", "minishell", cmd->command[0],
			cmd->command[1], "too many arguments\n");
		return (1);/*utilisée pour indiquer d'erreur*/
	}
	return (0);
}
