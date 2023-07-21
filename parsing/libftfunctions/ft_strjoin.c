/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:55:10 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/21 17:57:26 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *ft_strjoin(char *s1, char *s2)
{
    int i;
    int j;
    int len;
    char *ptr;

    len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
    if (s1 == NULL || s2 == NULL)
        return NULL;
    ptr = (char *)malloc(len * sizeof(char));
    if (!ptr)
        return NULL;
    i = 0;
    while (s1[i] != '\0')
    {
        ptr[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j] != '\0')
    {
        ptr[i + j] = s2[j];
        j++;
    }
    ptr[i + j] = '\0';
    return (ptr);
}