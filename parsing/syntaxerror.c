/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:42:46 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/21 12:24:42 by yochakib         ###   ########.fr       */
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
    int    i;

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

void	reset_inquotevalues(char	*command)
{
	int len = ft_strlen(command);
	int i = 0;
	int inquote = 0;

	while (i < len)
	{
		if (command[i] == '\'' || command[i] == '\"')
			inquote = !inquote;
		if (inquote)
		{
			if (command[i] < 0)
				command[i] *= -1;
			if (command[i] == '\'' || command[i] == '\"')
				i += 1;
		}
		i++;
	}
}

