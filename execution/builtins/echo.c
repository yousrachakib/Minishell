/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:17:30 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/17 18:59:30 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_check_ln(char *str)
{
	int i = 0;
	
	if(str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i] && str[i] == 'n')
			i++;
		if(str[i] == '\0')
				return(1);
		else if(str[i] != 'n')
			return(0);
	}
	return(0);
}

int ft_echo(char **cmd)
{
	int i = 1;
	if(!cmd[i])
		printf("\n");
	while(cmd[i] && ft_check_ln(cmd[i]) == 1)
	{
		i++;
		if(cmd[i] && !ft_check_ln(cmd[i]))
			ft_putstr_fd(cmd[i] , 1);
		if(cmd[i][0])
			ft_putstr_fd(" " , 1);
		i++;
	}
	if(cmd[i] && !ft_check_ln(cmd[i]) && cmd)
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i] , 1);
			if(&cmd[i])
				ft_putstr_fd(" " , 1);
			i++;
		}
		printf("\n");
	}
	return(0);
}

int main (int ac, char **av )
{
	ft_echo(av);
}