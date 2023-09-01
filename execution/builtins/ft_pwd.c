/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:20:37 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 21:33:53 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	buffer[1024];
	size_t	size;

	size = sizeof(buffer);
	getcwd(buffer, size);
	ft_putstr_fd(buffer, 1);
	ft_putstr_fd("\n", 1);
}

void	ft_check_k(t_shellcmd *cmd)
{
	if (cmd == NULL || !cmd->command[0])
		return ;
	signal(SIGQUIT, handlequit);
}
