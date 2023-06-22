/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:22:00 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/22 14:32:22 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int check_quotes(char *input)
{
    int i;
    int singlequote;
    int doublequote;

    i = 0;
    singlequote = 0;
    doublequote = 0;
    while (input[i])
    {
        if (input[i] == '\'')
            singlequote++;
        else if (input[i] == '\"')
            doublequote++;
        i++;
    }
    if (input[0] == '\"' && ((doublequote % 2) != 0))
        return (1);
    if (input[0] == '\'' && ((singlequote % 2) != 0))
        return (1);
    return (0);
}



int	special_char_only(char *input)
{
	int	i;

	i = 0;
	if (check_special(input[0])) // handlimg single special char
		return (1);
	while (input[i])
		i++;
	if (check_special(input[i - 1])) // handling special char at the end
		return (1);
	return (0);
}