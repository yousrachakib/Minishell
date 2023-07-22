/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:17:30 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/21 18:20:32 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_check_ln(char *str)
{
	int i = 0;
	
	if(str[i] != '\0' && str[i] == '-' && str[i + 1] == 'n' )
	{
		i++;
		while (str[i] != '\0'&& str[i] == 'n')
			i++;
		if(str[i] == '\0')
			return(1);
		else if(str[i] != 'n')
			return(0);
	}
	return(0);
}

void ft_print_new_ln(char **cmd , int flag)
{
	int i = 0;
	if(cmd[i] && !ft_check_ln(cmd[i]) && cmd && flag == 0)
	{
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i] , 1);
			if(cmd[i] != NULL)
				ft_putstr_fd(" " , 1);
			i++;
		}
		printf("\n");
	}
}

int ft_echo(char **cmd)
{
	int i = 2;
	int flag = 0;
	
	if(!cmd[i])
		printf("\n");
	while(cmd[i] != NULL && ft_check_ln(cmd[i]) == 1)
	{
		i++;
		flag = 1;
	}
	if(flag == 1 && cmd[i] && !ft_check_ln(cmd[i]) && cmd)
	{
		while (cmd[i])
		{
			if(cmd[i] != NULL) 
				ft_putstr_fd(cmd[i] , 1);
			ft_putstr_fd(" " , 1);
			i++;
		}
	}
	ft_print_new_ln(&cmd[i] , flag);
	exit(1);
}

// int main (int ac, char **av , char **env )
// {
// 	// printf("%s\n" , env[8]);
// 	ft_echo(av);
// }