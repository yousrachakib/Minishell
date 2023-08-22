/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/22 20:39:14 by yochakib         ###   ########.fr       */
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
# include <string.h>
# include <limits.h>
#include <sys/stat.h>
# include <signal.h>

extern int	status_exit;

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

typedef struct s_expand
{
	int		i;
	int		j;
	int		k;
	int		end;
	int		start;
	char	*temp;
	char	*input;
	char	*keytosearch;
}	t_expand;

typedef struct s_shellcmd
{
	char			**command;
	
	int				fd_in;//0
	int				fd_out;//1
	int				error_flag;
	
	struct s_shellcmd	*next;
}	t_shellcmd;

typedef struct s_cmd
{
	char			*input;
	int				flag_var;
	int				here_doc;
	t_type	type;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				flag;
	int				flag_env;
	struct s_env	*previous;
	struct s_env	*next;
}	t_env;



void	ft_putstr_fd(char *str, int fd);
int	ft_strlen(char *str);
void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd **list, t_expand *var);
int		check_quotes(char *input);
int		syntaxerror(t_cmd **list);
int		pipe_error_secondcase(t_cmd *list);
int		pipe_error_firstcase(t_cmd *list);
int		redirection_error(t_cmd *list);
int		begin_end_oflist(t_cmd *list);
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
int		handle_singleq(char *input, int *i, t_cmd **head);
int		handle_doubleq(char *input, int *i, t_cmd **head);
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
void	check_and_expand(t_env  *envlist, t_cmd *commandlist, t_expand	*var);
char	*ft_itoa(int n);
int		ft_isalnum(int c);
char	*ft_strjoin(char *s1, char *s2);
char	*join_commands(t_cmd *commandlist);
char	**ft_split(char *s, char c);
void	protect_dumbquote(char *input);
int		checkredirection(char c);
int		size_command(t_cmd *command);
void    findredirection(t_env *env,t_shellcmd   *command);
void	*ft_calloc(size_t count, size_t size);
void	addback_shellnode(t_shellcmd **head, t_shellcmd *newnode);
t_shellcmd	*create_shellnode(char **command);
void set_nonvalidcommand(char **command);
char	**copy2(char **command);
void	check_and_apply(t_shellcmd *list);
void	find_here_doc(t_env *env, t_shellcmd *list, t_expand *var);
char    *here_doc_expand(t_env   *env, char *input, t_expand *var);
int	verify_emptystring(char *str);
void	fill_heredoc_var(t_cmd	**command);
void	init_expand(t_expand	*var);
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
int		ft_echo(t_shellcmd *cmd);
int		ft_isalpha(int arg);
int		ft_isdigit(int arg);
int		ft_exit(t_shellcmd *cmd);
int		ft_atoi(char *str);
int		ft_printf(const char *str, ...);
int		ft_strncmp(const char *first, const char *second, size_t len);
void	ft_pwd(void);
char	*ft_strjoin(char  *s1, char  *s2);
char    **ft_split(char *s, char c);
void	**ft_free(char **s);
void	ft_env (t_env *env, t_shellcmd *cmd);
void	ft_execution (t_shellcmd *cmd, t_env **shellenv );
int		ft_exec_builtins(t_shellcmd *cmd  , t_env **env);
int		ft_chercher_builtins(t_shellcmd *cmd ,t_env *env);
void	ft_exec_path(t_shellcmd *cmd, t_env *shellenv );
char	*git_path(t_env *env);
char	*ft_check_path(char **spl, char *cmd);
char	*ft_path(char **spl, char *cmd);
void	ft_cd(t_shellcmd *cmd , t_env **env);
void	change_pwd(t_shellcmd *cmd  , t_env *env);
void	ft_oldpwd(t_env *env , char *str);
void	ft_unset(t_shellcmd *cmd, t_env **env);
void	ft_export(t_shellcmd *cmd,t_env **env);
int		ft_check_cmd(char *str);
void	add_cmd(t_env *env , t_shellcmd *cmd , int i , char **key);
void	ajouter_keyvaleur(t_env **env, char *str, char **key);
t_env	cree_node(char *key, char *value);
void	ft_add_liste(t_env *head, t_env *new_node);
int		modifier_env(t_env **env, char *command);
void	ft_creefork(char *s , t_shellcmd *cmd, char **newenv);
char	**ft_envirenment(t_env *shellenv);
int		countnodes(t_env *head) ;
void	sighandler(int sig);
void	ft_freearr(char **s);
int		ft_change_env(char **key , t_env *current , int flag);
void	ft_pipe(t_shellcmd *cmd, t_env **shellenv);
void	ft_getpath(t_shellcmd *cmd , t_env **shellenv);
void	pipe_exec_cmd(t_shellcmd *cmd, t_env **shellenv);
int		checkkeyexport(char* str);
char	**check_plusegal_cmd(t_env *current, char *command, int j);
void	cas_erreur(void);
void	addencas_env_null(t_env **env , char *command);
void	env_null(t_env **env);
void	ft_check_commande(t_shellcmd *cmd, t_env **shellenv);
void	suite_execution(t_shellcmd *cmd, t_env **shellenv);
void	handler_c(int signo);
void	ft_file(t_shellcmd *cmd, int pipfd[2]);
void	ft_close_fd(t_shellcmd *cmd, int pipfd[2]);
void	ft_directory(char *s, t_shellcmd *cmd, t_env *shellenv);
void	ft_message_erreur(char *s1, char *s2, char *s3);
void	ft_erreur_access(char *path, char *cmd);
void	ft_path_erreur(char *cmd);
char	*ft_home(t_shellcmd *cmd, t_env **env);
void	ft_pipe_erreur();
// void	ft_chech_derectory(char *s, t_shellcmd *cmd, char	**newenv);
#endif

