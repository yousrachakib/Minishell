/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:56:54 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/21 20:40:05 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	statustype(char *str)
{
	ft_printf("%e: numeric argument required\n", str);
	status_exit = 255;
	return (status_exit);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	res;
	long long	save;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		save = res;
		res = (res * 10) + (str[i] - 48);
		if (res / 10 != save)
			return (statustype(str));
		i++;
	}
	return (res * sign);
}

void	ft_pipe_erreur(void)
{
	perror("an error with opening the pipe\n");
	status_exit = 1;
}
