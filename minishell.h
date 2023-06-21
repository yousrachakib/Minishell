/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesbahi <mmesbahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 07:47:21 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/21 20:24:29 by mmesbahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_arg
{
    char *argument;
    struct s_arg *head;
    struct s_arg *next;
}  t_arg;

typedef struct s_export t_export;
typedef struct s_env t_env ;

typedef struct s_export 
{
    char *key;
    char *value;  
    t_export *next;
} t_export;
typedef struct s_env //stores the environment
{
    char *key;
    char *value;
    t_env *next;
} t_env;

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
typedef struct s_data //stores the general data of the shell
{
    t_cmd *cmd;
    char **line;
    t_env *env;
    t_export  *export;
} t_data;


char	**ft_split(char const *s, char *c);
void	*freeme(char **p);
void	*ft_memcpy(void *dst, const void *src, size_t len);
t_cmd *init_cmd(t_cmd *command);
t_arg *init_arg(t_arg *argument);
void parsing(char **res,t_cmd *command);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
t_export *create_nodee_export(char *key, char *val);
int parse_env(char **str, t_data **data);
void	ft_lstadd_backexport(t_export **lst, t_export *new);
void	excecution(t_env *env, t_data **data, char **envp);
void    cd(t_env *env, char **line);
void    echo(t_data *data, char **line);
void	export(char **line, t_export *export);
void    nrml_commands(t_env *env, t_data **data, char **envp);
void    pwd(t_env *env, char *cmd);
char	*ft_strjoin(char const *s1, char const *s2);
void	sort_list(t_export **head);
char **split_nodes(char *s, char c);


#endif