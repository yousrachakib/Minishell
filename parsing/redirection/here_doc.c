/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:07:37 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/30 22:56:49 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    handle_heredoc(t_env    *env,char *tofind)
{
    int fd;
    char *input;
    char *temp;
    int num = random();
    char *name = ft_itoa(num);
    char *name2 = ft_strjoin(ft_strdup("/tmp/temp"), name);
    free(name);
    fd = open(name2, O_WRONLY | O_CREAT , 0777);
    if (fd == -1)
    {
        ft_putstr_fd("Error file not found", 2);
    }
    while(1)
    {
        input = readline(">");
        if (ft_strcmp(input,tofind) != 0)
        {
            temp = here_doc_expand(env,input);
            free(input);
            input = temp;
            ft_putstr_fd(input, fd);
            ft_putstr_fd("\n", fd);
            free(input);
        }
        else
            break;
    }
}

void	find_here_doc(t_env *env,t_shellcmd *list)
{
    int i;
    t_shellcmd *temp;
    temp = list;
    while (temp)
    {
        i = 0;
        while (temp->command[i])
        {
            if (temp->command[i][0] == '<' && temp->command[i][1] == '<')
                handle_heredoc(env ,temp->command[i + 1]);
            i++;
        }
        temp = temp->next;
    }
}