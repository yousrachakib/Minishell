/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:24:04 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/27 14:21:21 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int checkredirection(char c)
// {
//     if (c == '>' || c == '<')
//         return (1);
//     return (0);
// }

// char *retrievefile(char *str)
// {
//     int i;
//     int j;
    
//     i = 0;
//     j = 0;
//     char *file; //need to dup;

//     while (str[i])
//     {
//         if (checkredirection(str[i]))
//         {
//             i += 1;
//             while (isalnum(str[i]))
//                 file[j++] = str[i++];
//             file[j] = '\0';
//         }
//     }
//     return (file);
// }