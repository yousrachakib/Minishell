/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:47:21 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/14 11:45:42 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_arg
{
    char *argument;
    struct s_arg *head;
    struct s_arg *next;
}  t_arg;

typedef struct s_cmd
{
    char    *cmd;
    char    *option; //check '-'
    t_arg *arg; // in case of argument
    char *stin; // >
    char *stout; // <
    char *stin2; // <<
    char *stout2; // >>
    struct s_cmd   *head; // pipe | 
    struct s_cmd   *next; // pipe case
}   t_cmd;


char	**ft_split(char const *s, char *c);
void	*freeme(char **p);
void	*ft_memcpy(void *dst, const void *src, size_t len);
t_cmd *init_cmd(t_cmd *command);
t_arg *init_arg(t_arg *argument);
void parsing(char **res,t_cmd *command);

#endif