/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:20:37 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/15 21:11:53 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd(void)
{
	char buffer[1024];
	size_t size = sizeof(buffer);
	
	if (getcwd(buffer, size) != NULL )
	{
		ft_putstr_fd(buffer, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		perror("Erreur lors de la récupération du répertoire de travail");
}

int main() 
{
    ft_pwd();
    return 0;
}