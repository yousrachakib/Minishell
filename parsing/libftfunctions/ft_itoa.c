/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 00:18:39 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/28 20:29:58 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_count(int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	*ft_copy(char *ptr, int n, int len)
{
	ptr[len] = '\0';
	while (len > 0)
	{
		len--;
		ptr[len] = n % 10 + 48;
		n = n / 10;
	}
	return (0);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
	{
		n = n * (-1);
		len = ft_count(n) + 1;
		ptr = ft_calloc(sizeof(char) * len + 1, 1);
		if (!ptr)
			return (0);
		ft_copy(ptr, n, len);
		ptr[0] = '-';
		return (ptr);
	}
	else
	{
		len = ft_count(n);
		ptr = ft_calloc(sizeof(char) * len + 1, 1);
		if (!ptr)
			return (0);
		ft_copy(ptr, n, len);
		return (ptr);
	}
}