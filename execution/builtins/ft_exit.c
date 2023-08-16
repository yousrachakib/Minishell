/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/14 22:25:49 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_shellcmd *cmd)
{
	int		i;

	i = 0;
	if (!cmd->command[1])
		exit (0);
	while (cmd->command[1][i])
	{
		if (ft_isalpha(cmd->command[1][i]))
		{
			ft_printf("%e :%e : %e : %e", "minishell", cmd->command[0],
				cmd->command[1], "numeric argument required");
			status_exit = 255;
			exit (status_exit);
		}
		i++;
	}
	if (!cmd->command[2])
		exit (ft_atoi(cmd->command[1]));
	else 
	{
		ft_printf("%e :%e : %e : %e", "minishell", cmd->command[0],
			cmd->command[1], "too many arguments\n");
		status_exit = 1;
		return (1);
	}
	return (0);
}
