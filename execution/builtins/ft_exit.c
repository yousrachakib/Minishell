/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:50:21 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/16 16:12:20 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_exit(char **cmd)
{
	int i;
	int j = 1;
	if(!cmd[1])
		exit(127);/* indiquer une erreur de commande introuvable.*/
	while (cmd[j])
	{
		i = 0;
		while(cmd[j][i])
		{
			if(cmd[j][i] && ft_isalpha(cmd[j][i]))
			{
				printf("%s : %s : %s", cmd[0], cmd[j], "numeric argument required");
					exit(255);/*utilisée pour indiquer d'erreur*/
			}
			i++;
		}
		if(!cmd[j])
			exit(127);
		else
			printf("%s : %s " , cmd[0] ,"too many arguments\n");
				exit(255);/*utilisée pour indiquer d'erreur*/
		j++;
	}
	return(0);
}
int main (int ac, char **av)
{
	ft_exit(av);
}