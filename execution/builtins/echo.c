/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:17:30 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/13 20:24:24 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_check_ln(char *str)
{
	if(str[0] == '-' && str[1] == 'n' && str[2] == '\0')
		return(1);
	else if(str[0] == '-' && (str[1] != 'n' || str[2] != '\0'))
		return (0);
	else
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
		if(!ft_check_ln(cmd[i]) && cmd[i])
		{
			ft_putstr_fd(cmd[i] , 1);
			if(cmd[i][0])
				ft_putstr_fd(" " , 1);
		}
	}
	
	i = 1;
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

int main (int ac, char **av)
{
	ft_echo(av);
}