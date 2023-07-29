/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/29 22:33:42 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

int	status_exit;

typedef enum s_type
{
	t_space,
	t_word,
	t_pipe,
	t_input,
	t_singlequote,
	t_doublequote,
	t_output,
	output_apnd,
	here_doc,
}	t_type;

typedef struct s_shellcmd
{
	char			**command;
	int				fd_in;
	int				fd_out;
	struct s_shellcmd	*next;
}	t_shellcmd;

typedef struct s_cmd
{
	char			*input;
	int				flag_var;
	t_type	type;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*previous;
	struct s_env	*next;
}	t_env;



void	ft_putstr_fd(char *str, int fd);
int	ft_strlen(char *str);
void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd **list);
int		check_quotes(char *input);
int		syntaxerror(t_cmd **list);
int		is_whitespace(char c);
int		check_special(char c);
char	*ft_substr(char *input,int start,int len);
t_cmd	*create_node(char *splited_input, t_type type);
t_cmd	*last_node(t_cmd	*node);
void	addback_node(t_cmd **head, t_cmd *newnode);
void	reset_inquotevalues(char	*command);
void	protect_inquote(char *input);
void	separators_case(char *input, int *i, t_cmd **head);
void	whitespace_case(char *input, int *i, t_cmd	**head);
int		quotation_case(char *input, int *i, t_cmd **head);
void	word_case(char *input, int *i, t_cmd **head);
t_cmd 	**tokenizer(char *input);
t_env	*create_envnode(char *key, char *value);
void	addback_envnode(t_env **head, t_env *newnode);
char *retrieve_key(char *line);
char	*ft_strchr(char *s, int c);
char	*ft_strncpy(char *dest, char *src,int n);
char *retrieve_value(char *line);
char	*ft_strdup(char *s1);
void    creat_env_struct(char **environment, t_env **final_list);
int		ft_strcmp(char *str1,char *str2);
void    check_and_expand(t_env  *envlist, t_cmd *commandlist);
char	*ft_itoa(int n);
int		ft_isalnum(int c);
char	*ft_strjoin(char *s1, char *s2);
char	*join_commands(t_cmd *commandlist);
char	**ft_split(char *s, char c);
void	protect_dumbquote(char *input);
int		checkredirection(char c);
int		size_command(t_cmd *command);
void	findredirection(t_shellcmd   *command);
void	*ft_calloc(size_t count, size_t size);
void	addback_shellnode(t_shellcmd **head, t_shellcmd *newnode);
t_shellcmd	*create_shellnode(char **command);
void set_nonvalidcommand(char **command);

#endif