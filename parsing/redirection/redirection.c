/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:28:58 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/27 21:24:55 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shellcmd    *findredirection(t_cmd   *command)
{
    t_shellcmd *finallist;
    t_shellcmd *head;
    int i;
    finallist = malloc(sizeof(t_shellcmd));
    finallist->command = malloc(sizeof(char *) * (size_command(command) + 1));
    finallist->next = NULL;
    head = finallist;
    i = 0;
    finallist->fd_in = 0; 
    finallist->fd_out = 1;
    while (command)
    {
        if (command->type == here_doc || command->type == t_input || command->type == t_output || command->type == output_apnd)
        {
            t_cmd *current = command;
            if (command->next->type == t_space)
                command = command->next;
            if (current->type == t_input)
            {
                if ( finallist->fd_in != 0 )
                    close(finallist->fd_in);
                finallist->fd_in = open(command->next->input, O_RDONLY);
                if (finallist->fd_in < 0)
                {
                    perror("cuteshell ");
                    return (NULL);
                }
            }
            if (current->type == t_output)
            { 
                if ( finallist->fd_out != 1)
                    close(finallist->fd_out);
                finallist->fd_out = open(command->next->input, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (finallist->fd_out < 0)
                {
                    perror("cuteshell ");
                    return (NULL);
                }
            }
            if (current->type == output_apnd)
            {
                if ( finallist->fd_out != 1)
                    close(finallist->fd_out);
                finallist->fd_out = open(command->next->input, O_WRONLY | O_CREAT | O_APPEND, 0666);
                if (finallist->fd_out < 0)
                {
                    perror("cuteshell ");
                    return (NULL);
                } 
            }
            command = command->next;
        }
        else if (command->type == t_pipe)
        {
            finallist->command[i] = NULL;
            i = 0;
            finallist->next = malloc(sizeof(t_shellcmd));
            finallist = finallist->next;
            finallist->command = malloc(sizeof(char *) * (size_command(command) + 1));
            finallist->next = NULL;
            finallist->fd_in = 0; 
            finallist->fd_out = 1;
        }
        else if (command->type != t_space)
        {
            finallist->command[i] = ft_strdup(command->input);
            i++;
        }
        if (command)
            command = command->next;
    }
    finallist->command[i] = NULL;
    return(head);
}

int size_command(t_cmd *command)
{
    int i;

    i = 0;
    while (command && command->type != t_pipe)
    {
        
        if (command->type == here_doc || command->type == t_input || command->type == t_output || command->type == output_apnd)
            command = command->next;
        else if (command->type != t_space)
            i++;
        command = command->next;
    }
    return (i);
}
