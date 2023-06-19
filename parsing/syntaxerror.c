/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:42:46 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/19 17:49:43 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	protect_inquote(char *input)
{
	int	len;
	int	i;
	int	inquote;

	i = 0;
	len = ft_strlen(input);
	inquote = 0;
	while (i < len)
	{
		if (input[i] == '\'' || input[i] == '\"')
			inquote = !inquote;
		if (inquote)
		{
			if (input[i] == '\'' || input[i] == '\"')
				i += 1;
			input[i] *= -1;
		}
		i++;
	}
}
