/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesbahi <mmesbahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 18:02:07 by mmesbahi          #+#    #+#             */
/*   Updated: 2023/06/09 19:13:52 by mmesbahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void    ft_putstr(char *str)
{
    int i = 0;

    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}
void    echo(t_data *data, char **line)
{
    (void)data;
    int  i = 1;

    while (line[i])
    {
        ft_putstr(line[i]);
        write (1, " ", 1);
        i++;
    }
    write (1, "\n", 1);
}