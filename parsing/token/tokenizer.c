/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:03:32 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/25 17:08:21 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	// printf("ptr dup : %s\n", ptr);
	return (ptr);
}

char	*ft_substr(char *input,int start,int len)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = 0;
	if (!input)
		return (NULL);
	if (start >= ft_strlen(input))
		return (ft_strdup(""));
	if (len >= ft_strlen(input))
		ptr = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	else
		ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (input[++i])
	{
		if (i >= start && j < len)
			ptr[j++] = input[i];
	}
	ptr[j] = '\0';
	return (ptr);
}


int	check_special(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

t_cmd **tokenizer(char *input)
{
	t_cmd	**command_list;
	int 	i;

	i = 0;
	command_list = malloc(sizeof(t_cmd *));
	if (!command_list)
		return (NULL);
	*command_list = NULL;
	while (input[i])
	{
		if (input[i] && is_whitespace(input[i]))
			whitespace_case(input ,&i, command_list);
		else if (input[i] && check_special(input[i]))
			separators_case(input, &i, command_list);
		else if (input[i] && (input[i] == '\"' || input[i] == '\''))
		{
			if (quotation_case(input, &i, command_list) == 1)
				return (NULL);
		}
		else
			word_case(input, &i, command_list);
	}
	return (command_list);
}