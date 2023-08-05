/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:56:54 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/05 13:51:53 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	long long	res;
	long long save;

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
		res = res * 10;
		res = res + str[i] - 48;
		if (res / 10 != save)
		{
			ft_printf("%e: numeric argument required\n", str);
			return (255);
		}
		i++;
	}
	return (res * sign);
}
