/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_finallist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:49:06 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/26 20:20:24 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *join_commands(t_cmd *commandlist)
{
	t_cmd *currentcmd;
	char *joined_commands;
	
    currentcmd = commandlist;
    if (commandlist == NULL)
        return NULL;
    joined_commands = ft_strdup("");
    while (currentcmd)
    {
		if (currentcmd->flag_var == 2 || currentcmd->flag_var == 1)
            protect_dumbquote(currentcmd->input);
        joined_commands = ft_strjoin(joined_commands, currentcmd->input);
        currentcmd = currentcmd->next;
    }
    return (joined_commands);
}

void free_joined_commands(char *joined_commands)
{
    free(joined_commands);
}
