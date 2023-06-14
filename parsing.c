/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 11:12:41 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/14 11:42:26 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_cmd(char **res, t_cmd *command)
{    
    int i;
    
    i = 0;
    while (res[i])
    {
        if (res[i][0] == '-')
            command->option = res[i];
        else if (((res[i][0] >= 'A' && res[i][0] <= 'Z') || \
            (res[i][0] >= 'a' && res[i][0] <= 'z')) && command->cmd == NULL)
            command->cmd = res[i];
        else if (res[i][0] == '>' && res[i][1] != '>')
            command->stin = res[i];
        else if (res[i][0] == '<'&& res[i][1] != '<')
            command->stout = res[i];
        else if (res[i][0] == '>' && res[i][1] == '>')
            command->stin2 = res[i];
        else if (res[i][0] == '<' && res[i][1] == '<')
            command->stout2 = res[i];
        else if (command->cmd != NULL)
            command->arg->argument = res[i];
        i++;
    }
}

void parsing(char **res,t_cmd *command)
{

    init_cmd(command);
    init_arg(command->arg);
    fill_cmd(res, command);
    printf("---->%s", command->arg->argument);
    printf("---->%s", command->cmd);
    printf("---->%s", command->option);
    printf("---->%s", command->stin);
    printf("---->%s", command->stin2);
    printf("---->%s", command->stout2);
    printf("---->%s", command->stout);

}