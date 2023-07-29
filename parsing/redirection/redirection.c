/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:28:58 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/29 22:34:13 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    findredirection(t_shellcmd   *command)
{
    int i;
    i = 0;
    while (command->command[i])
    {
        if (command->command[i][0] == '>' || command->command[i][0] == '<' || \
            (command->command[i][0] == '>' && command->command[i][1] == '>'))
        {
            if (command->command[i][0] == '>')
            {
                if (command->fd_in != 0)
                    close(command->fd_in);
                command->fd_in = open(command->command[i + 1], O_RDONLY);
                if (command->fd_in < 0)
                {
                    perror("cuteshell ");
                    // return (NULL);
                }
            }
            if (command->command[i][0] == '<')
            { 
                if ( command->fd_out != 1)
                    close(command->fd_out);
                command->fd_out = open(command->command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (command->fd_out < 0)
                {
                    perror("cuteshell ");
                    // return (NULL);
                }
            }
            if ((command->command[i][0] == '>' && command->command[i][1] == '>'))
            {
                if ( command->fd_out != 1)
                    close(command->fd_out);
                command->fd_out = open(command->command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
                if (command->fd_out < 0)
                {
                    perror("cuteshell ");
                    // return (NULL);
                } 
            }
        }
    }
}