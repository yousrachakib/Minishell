/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:17:30 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/31 19:22:29 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_ln(char *str)
{
	int		i;

	i = 0;
	if (str[i] != '\0' && str[i] == '-' && str[i + 1] == 'n' )
	{
		i++;
		while (str[i] != '\0' && str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
		else if (str[i] != 'n')
			return (0);
	}
	return (0);
}

void	ft_print_new_ln(char **cmd, int flag)
{
	int		i;

	i = 0;
	if (cmd[i] && !ft_check_ln(cmd[i]) && cmd && flag == 0)
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
		printf("\n");
	}
}

void	ft_commande(t_shellcmd *cmd, int i)
{
	if (cmd->command[i] != NULL) 
		ft_putstr_fd(cmd->command[i], 1);
	if (cmd->command[i + 1])
		ft_putstr_fd(" ", 1);
}

int	ft_echo(t_shellcmd *cmd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (!cmd->command[i])
		printf("\n");
	while (cmd->command[i] != NULL && ft_check_ln(cmd->command[i]) == 1)
	{
		i++;
		flag = 1;
	}
	if (flag == 1 && cmd->command[i] && !ft_check_ln(cmd->command[i]) && cmd)
	{
		while (cmd->command[i])
		{
			ft_commande(cmd, i);
			i++;
		}
	}
	ft_print_new_ln(&cmd->command[i], flag);
	g_j.status_exit = 0;
	return (g_j.status_exit);
}
