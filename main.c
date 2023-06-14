/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:58:08 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/14 17:30:40 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *init_cmd(t_cmd *command)
{
    t_cmd *tmp;
    
    tmp = malloc(sizeof(t_cmd));
    if (!tmp)
        exit(1);
    tmp->cmd = NULL;
    tmp->option = NULL;
    tmp->arg = NULL;
    tmp->head = tmp;
    tmp->next = NULL;
    tmp->stin = NULL;
    tmp->stout = NULL;
    tmp->stin2 = NULL;
    tmp->stout2 = NULL;
    return (tmp);
}

t_arg *init_arg(t_arg *argument)
{
    t_arg *tmp;
    
    tmp = malloc(sizeof(t_arg));
    if (!tmp)
        exit(1);
    argument->argument = NULL;
    argument->head = tmp;
    argument->next = NULL;
    return (tmp);
}
int main() 
{
    t_cmd   *command;
    char *input;
    char **res;
    while (1) 
    {
        // Display the prompt and read user input
        input = readline("$> ");
        if (input == NULL) // Handle end-of-file (Ctrl+D) condition
            break;
        res = ft_split(input, "     ");
        // Add the user input to the history
        if (input[0] != '\0')
            add_history(input);
        parsing(res, command);
    }
    return (0);
}
