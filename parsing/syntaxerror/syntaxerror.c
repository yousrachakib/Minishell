/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:42:46 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/01 14:20:38 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	protect_inquote(char *input)
{
	int	i;

	if (!input[0] || !input)
		return ;
	i = 0;
	while (input[i])
	{
		if (input[i] == 39)
		{
			i++;
			while (input[i] != 39 && input[i])
				input[i++] *= -1;
		}
		if (input[i] == 34)
		{
			i++;
			while (input[i] != 34 && input[i])
				input[i++] *= -1;
		}
		i++;
	}
}

void	protect_dumbquote(char *input)
{
	int	i;

	if (!input[0] || !input)
		return ;
	i = 0;
	while (input[i])
	{
		input[i++] *= -1;
	}
}

void	reset_inquotevalues(char	*command)
{
	int	i;
	int	len;

	len = ft_strlen(command);
	if (!command[0] || !command)
		return ;
	i = 0;
	while (i < len)
	{
		if (command[i])
			command[i] *= -1;
		i++;
	}
}
