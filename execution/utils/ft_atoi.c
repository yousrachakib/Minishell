/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:56:54 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/05 00:10:18 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	statustype(char *str)
{
	ft_printf("%e: numeric argument required\n", str);
	g_j.status_exit = 255;
	return (g_j.status_exit);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

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
		res = (res * 10) + (str[i] - 48);
		if ((res > 9223372036854775807U && sign == 1)
			|| (sign == -1 && res > 9223372036854775808U))
			return (statustype(str));
		i++;
	}
	return (res * sign);
}

void	ft_pipe_erreur(void)
{
	perror("an error with opening the pipe\n");
	g_j.status_exit = 1;
}

void	handlequit(int sig)
{
	(void)sig;
	printf("Quit: 3");
}

void	dup_close(int tmp_fd_in, int tmp_fd_out)
{
	int	status;
	int	i;

	i = 0;
	dup2(tmp_fd_in, 0);
	close(tmp_fd_in);
	dup2(tmp_fd_out, 1);
	close(tmp_fd_out);
	while (wait(&status) != -1)
		i++;
}
