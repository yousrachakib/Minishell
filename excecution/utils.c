/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesbahi <mmesbahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:02:37 by mmesbahi          #+#    #+#             */
/*   Updated: 2023/06/21 20:22:58 by mmesbahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup( const char *source)
{
	char	*p;
	int		i;

	p = (char *)malloc(ft_strlen(source) + 1 * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (source[i])
	{
		p[i] = source[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	sub = malloc (len + 1 * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (s[i] && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = (char *)malloc(i + j + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
