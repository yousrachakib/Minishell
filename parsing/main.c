/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/15 20:02:43 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(t_info *info)
{
    int i;
    int singlequote;
    int doublequote;

    i = 0;
    singlequote = 0;
    doublequote = 0;
    while (info->input)
    {
        if (info->input[i] == '\'')
            singlequote++;
        if(info->input[i] == '\"')
            doublequote++;
        i++;
    }
    if ((singlequote % 2) != 0 || (doublequote % 2) != 0)
        return (0);
    return (1);
}

void syntaxerror(t_info *info)
{
    if (check_quotes(info->input))
    {
        printf("syntaxError : verify quotations\n");
        free(info->input);
        continue;
    }
}

void    ft_readline(t_info *info)
{
    char *trimmedINPUT;
    while(1)
    {
        info->input = readline("$> ");
        if (info->input == NULL)
            break; //handling EOF control+D
        trimmedINPUT = info->input;
        while (*trimmedINPUT == ' ' || *trimmedINPUT == '\t') //making sure no spaces at the beginning 
            trimmedINPUT++;
        if (trimmedINPUT[0] != '\0')
            add_history(trimmedINPUT);
    }
}



int main(int ac, char **av)
{
    char *res;
    ft_readline(res);
}