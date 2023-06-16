/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/16 20:01:56 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void syntaxerror(char *input)
{
    if (check_quotes(input))
    {
        printf("syntaxError : verify quotations\n");
        free(input);
        return ;
    }
    if (pipe_errors(input))
    {
        printf("syntaxError : verify pipe\n");
        free(input);
        return ;
    }
}

void ft_readline(char *input)
{
    while(1)
    {
        input = readline("$> ");
        if (input == NULL)
            break; //handling EOF control+D
        if (input[0] != '\0')
            add_history(input);
        syntaxerror(input);
    }
}

int main(int ac, char **av)
{
    char *input;
    ft_readline(input);
}