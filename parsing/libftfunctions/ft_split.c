/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 21:04:37 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/05 12:28:18 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	ft_count_split(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && c != s[i])
			i++;
		if (c == 0)
		{
			count++;
			break ;
		}
		while (c && c == s[i])
			i++;
		count++;
	}
	return (count);
}

static	int	ft_count_word(char *s, char c)
{
	int	count;

	count = 0;
	while (*s && c != *s)
	{
		count++;
		s++;
	}
	return (count);
}

static	char	*ft_word(char *s, char c, char **word)
{
	int	count;
	int	i;

	count = ft_count_word(s, c);
	*word = ft_calloc((count + 1) * sizeof(char), 1);
	if (!word)
		return (0);
	(*word)[count] = 0;
	i = 0;
	while (i < count)
		(*word)[i++] = *s++;
	while (c == *s)
		s++;
	return (s);
}

static	int	_free_(char **res, int size)
{
	while (size--)
	{
		free(res[size]);
	}
	free(res);
	return (0);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**res;
	int		count;

	if (s == 0)
		return (NULL);
	i = 0;
	while (c && *s && c == (char) *s)
		s++;
	count = ft_count_split((char *)s, c);
	res = ft_calloc((count + 1) * sizeof(char *), 1);
	if (!res)
		return (0);
	res[count] = 0;
	i = 0;
	while (i < count)
	{
		s = ft_word((char *)s, c, res + i);
		if (!s)
			_free_(res, i);
		i++;
	}
	return (res);
}