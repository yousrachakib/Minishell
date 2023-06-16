/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:22:00 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/16 20:51:26 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        if(input[i] == '\"')
            doublequote++;
        i++;
    }
    if ((singlequote % 2) != 0 || (doublequote % 2) != 0)
        return (1);
    return (0);
}
int check_special(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);
}
int special_char_only(char *input)
{
    int i;
    
    i = 0;
    if (check_special(input[0]))
        return (1);
    while (input[i])
        i++;
    if (check_special(input[i - 1]))
        return (1);
    return (0);
}
 
int pipe_errors(char *input)
 {
    int i;

    i = 0;
    while ( input[i] && is_whitespace(input[i]))
        i++;
    if (input[i] == '|') // pipe at end
        return (1);
    while (input[i])
    {
        if (check_special(input[i]) && check_special(input[i + 1]) && input[i + 2] == '|') // (<< |)( >> |)
			return (1);
        if (check_special(input[i] && input[i + 1] == '|')) // (< |)( > |)
			return (1);
		if (check_special(input[i]) && check_special(input[i + 1]) && check_special(input[i + 2]) && check_special(input[i + 3])) // (>> >>) (<< <<)
			return (1);
		if (check_special(input[i]) && check_special(input[i + 1])) // (< <) (> <)
			return (1);
		i++;
    }
	if (input[i - 1] == '|') // pipe at end
		return (1);
	return (0);
 }