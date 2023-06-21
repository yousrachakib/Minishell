/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excecution_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesbahi <mmesbahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:06:17 by mmesbahi          #+#    #+#             */
/*   Updated: 2023/06/09 15:38:18 by mmesbahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char *input;
    t_data *data;
    int i = 0;
    
    data = malloc(sizeof(t_data) * 1);
    data->env = malloc (sizeof(t_env));
    data->export = malloc(sizeof(t_export));
    parse_env(env, &data);
    while (1)
    { 
        input = readline ("minishell -> ");
        data->line = ft_split(input, ' ');
        excecution(data->env, &data, env);
        i = 0;
        while (data->line[i])
            free(data->line[i++]);
        free(data->line);
    }
}