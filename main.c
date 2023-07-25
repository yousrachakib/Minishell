/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesbahi <mmesbahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 08:58:08 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/21 20:34:48 by mmesbahi         ###   ########.fr       */
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
int main(int ac, char **av, char **env) 
{
    t_cmd   *command;
    t_data *data;
    char *input;
    char **res;
    int i = 0;

    data = malloc(sizeof(t_data) * 1);
    data->env = malloc (sizeof(t_env));
    data->export = malloc(sizeof(t_export));
    parse_env(env, &data);
    while (1) 
    {
        // Display the prompt and read user input
        input = readline("Minishell$> ");
        if (input == NULL) // Handle end-of-file (Ctrl+D) condition
            break;
        data->line = ft_split(input, "     ");
        // Add the user input to the history
        if (input[0] != '\0')
            add_history(input);
        // parsing(data->line, command);
        excecution(data->env, &data, env);
        while (data->line[i])
            free(data->line[i++]);
        free(data->line);
    }
    return (0);
}
