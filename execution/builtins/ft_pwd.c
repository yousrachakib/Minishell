/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:20:37 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/06 12:18:20 by mben-sal         ###   ########.fr       */
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
