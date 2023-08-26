/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:22:00 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/26 18:29:18 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	verify_emptystring(char *str)
{
	int i  = 0;
	while (str[i] && is_whitespace(str[i]) == 1)
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
	
}

int	check_quotes(char *input)
{
	int	i;
	int	singlequote;
	int	doublequote;

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

void	word_case(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;
	int		j;
	char	*res;

	j = *i;
	while (input[j] && input[j] != '|' && input[j] != '<'
		&& input[j] != '>' && input[j] != '\'' && input[j] != '\"'
		&& !is_whitespace(input[j]))
		j++;
	res = ft_substr(input, (*i), (j - (*i)));
	if (!res)
		return ;
	node = create_node(ft_strdup(res), t_word);
	(*i) += j - (*i);
	free(res);
	addback_node(head, node);
}

int	quotation_case(char *input, int *i, t_cmd **head)
{
	if (input[*i] == '\'')
	{
		if (handle_singleq(input, i, head) == 1)
			return (1);
	}
	else if (input[*i] == '\"')
	{
		if (handle_doubleq(input, i, head) == 1)
			return (1);
	}
	return (0);
}
