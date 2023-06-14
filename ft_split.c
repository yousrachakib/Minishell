/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 09:26:01 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/14 09:40:59 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char) c;
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	return (0);
}

int	wordcnt(const char *str, char *c)
{
	int	i;
	int	cpt;

	cpt = 0;
	i = 0;
	while (str[i])
	{
		if ((ft_strchr(c, str[i + 1]) && !ft_strchr(c, str[i]))
			|| (!ft_strchr(c, str[i]) && str[i + 1] == '\0'))
			cpt++;
		i++;
	}
	return (cpt);
}

char	**lol(char **pt, const char *s, char *c)
{
	int		i;
	int		j;

	j = 0;
	while (*s)
	{
		i = 0;
		while (!ft_strchr(c, s[i]) && s[i] != '\0')
			i++;
		if (i > 0)
		{
			pt[j] = (char *)malloc((i + 1) * sizeof(char));
			if (!pt)
				return ((char **)freeme(pt));
			ft_memcpy(pt[j], s, i);
			pt[j][i] = '\0';
			j++;
			s = s + i;
		}
		else
			s++;
	}
	pt[j] = NULL;
	return (pt);
}

void	*freeme(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char		*src_cst;
	char		*dst_cst;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	src_cst = (char *)src;
	dst_cst = (char *)dst;
	i = 0;
	while (i < len)
	{
		dst_cst[i] = src_cst[i];
		i++;
	}
	return (dst_cst);
}

char	**ft_split(char const *s, char *c)
{
	char	**pt;

	if (!s)
		return (NULL);
	pt = (char **)malloc((wordcnt(s, c) + 1) * sizeof(char *));
	if (!pt)
		return (NULL);
	pt = lol (pt, s, c);
	return (pt);
}