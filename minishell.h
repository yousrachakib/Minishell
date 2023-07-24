/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/24 16:13:28 by mben-sal         ###   ########.fr       */
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
# include <stdarg.h>
# include <sys/errno.h>
# include <errno.h>

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
void	ft_readline(char *input, t_cmd	**command, t_env *final_list);
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
void findredirection(t_cmd	*finallist);
int	ft_isalnum(int c);



/*****************************************************************************/
/*                              execution                                    */
/*****************************************************************************/

typedef struct s_spl
{
	size_t	i;
	size_t	j;
	size_t	len;
	int		index;
	int		count;
	char	**ptr;
}	t_spl;
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_echo(char **cmd);
int		ft_isalpha(int arg);
int		ft_isdigit(int arg);
int		ft_exit(char **cmd);
int		ft_atoi(char *str);
int		ft_printf(const char *str, ...);
int		ft_strncmp(const char *first, const char *second, size_t len);
void	ft_pwd(void);
char	*ft_strjoin(char  *s1, char  *s2);
char    **ft_split(char *s, char c);
void	**ft_free(char **s);
int		ft_env (t_env *env , char *cmd);
void	ft_execution (char **cmd , t_env *env);
int		ft_exec_builtins(char **cmd , t_env *env);
int		ft_chercher_builtins(char *cmd ,t_env *env);
void	ft_exec_path(char *cmd, t_env *env);
char	*git_path(t_env *env);
char	*ft_check_path(char **spl, char *cmd);
char	*ft_path(char **spl, char *cmd);
void	ft_cd(char **cmd , t_env *env);
void	change_pwd(char **cmd , t_env *env);
void	ft_oldpwd(t_env *env , char *str);
void	ft_unset(char *cmd, t_env *env);
void	ft_export(char **cmd,t_env *env);
int		ft_check_cmd(char *str);
void	add_cmd(t_env *env , char **cmd , int i , char **key);
void	ajouter_keyvaleur(t_env *env ,t_env *courrant ,char **cmd, char **key);
t_env	cree_node(char *key, char *value);
void	ft_add_liste(t_env *head, t_env *new_node);

#endif
