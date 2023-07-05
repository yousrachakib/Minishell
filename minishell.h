/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/05 16:55:14 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_type
{
	t_word,
	t_pipe,
	t_input,
	t_singlequote,
	t_doublequote,
	t_output,
	output_apnd,
	here_doc,
}	t_type;

typedef struct s_cmd
{
	char			*input;
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
void	ft_readline(char *input);
int		check_quotes(char *input);
int		syntaxerror(t_cmd **list);
int		is_whitespace(char c);
int		check_special(char c);
int		special_char_only(char *input);
char	*ft_substr(char *input,int start,int len);
t_cmd	*create_node(char *splited_input, t_type type);
t_cmd	*last_node(t_cmd	*node);
void	addback_node(t_cmd **head, t_cmd *newnode);
void	reset_inquotevalues(char	*command);
void	protect_inquote(char *input);
void	separators_case(char *input, int *i, t_cmd **head);
void	whitespace_case(char *input, int *i);
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
void init_env(t_env *environment);

#endif