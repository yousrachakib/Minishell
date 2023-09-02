/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/02 16:10:35 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
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
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct s_file
{
	char			*filename;
	struct s_file	*next;
}	t_file;

typedef struct s_zdef
{
	int		signal;
	int		status_exit;
	t_file	*k;
}	t_zdef;

t_zdef	g_j;

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
	int		count;
	int		start;
	char	*temp;
	char	*input;
	char	*keytosearch;
}	t_expand;

typedef struct s_shellcmd
{
	char				**command;
	int					fd_in;
	int					fd_out;
	int					error_flag;
	struct s_shellcmd	*next;
}	t_shellcmd;

typedef struct s_cmd
{
	char			*input;
	int				flag_var;
	int				here_doc;
	t_type			type;
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

void		free_expandstruct(t_expand	*var);
void		free_list(t_cmd **command);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
void		ft_readline(char *input, t_cmd	**command,
				t_env *env, t_expand *var);
int			check_quotes(char *input);
int			syntaxerror(t_cmd **list);
int			pipe_error_secondcase(t_cmd *list);
int			pipe_error_firstcase(t_cmd *list);
int			redirection_error(t_cmd *list);
int			begin_end_oflist(t_cmd *list);
int			is_whitespace(char c);
int			check_special(char c);
char		*ft_substr(char *input, int start, int len);
t_cmd		*create_node(char *splited_input, t_type type);
t_cmd		*last_node(t_cmd	*node);
void		addback_node(t_cmd **head, t_cmd *newnode);
void		reset_inquotevalues(char	*command);
void		protect_inquote(char *input);
void		separators_case(char *input, int *i, t_cmd **head);
void		whitespace_case(char *input, int *i, t_cmd	**head);
int			handle_singleq(char *input, int *i, t_cmd **head);
int			handle_doubleq(char *input, int *i, t_cmd **head);
int			quotation_case(char *input, int *i, t_cmd **head);
void		word_case(char *input, int *i, t_cmd **head);
t_cmd		**tokenizer(char *input);
t_env		*create_envnode(char *key, char *value);
void		addback_envnode(t_env **head, t_env *newnode);
char		*retrieve_key(char *line);
char		*ft_strchr(char *s, int c);
char		*ft_strncpy(char *dest, char *src, int n);
char		*retrieve_value(char *line);
char		*ft_strdup(char *s1);
int			findredirection(t_env *env, t_shellcmd *command, t_expand *var);
void		creat_env_struct(char **environment, t_env **env_list);
int			ft_strcmp(char *str1, char *str2);
void		check_and_expand(t_env *envlist, t_cmd *commandlist, t_expand *var);
char		*ft_itoa(int n);
int			ft_isalnum(int c);
char		*ft_strjoin(char *s1, char *s2);
char		*join_commands(t_cmd *commandlist);
char		**ft_split(char *s, char c);
void		protect_dumbquote(char *input);
int			checkredirection(char c);
int			size_command(t_cmd *command);
char		**copy2(char **command);
void		remove_redirandfilename(char *command);
void		*ft_calloc(size_t count, size_t size);
void		addback_shellnode(t_shellcmd **head, t_shellcmd *newnode);
void		set_nonvalidcommand(char **command);
char		**copy2(char **command);
void		check_and_apply(t_shellcmd *list);
int			find_here_doc(t_env *env, t_shellcmd *list, t_expand *var);
char		*here_doc_expand(t_env *env, char *input, t_expand *var);
int			verify_emptystring(char *str);
void		fill_heredoc_var(t_cmd	**command);
void		init_expand(t_expand	*var);
void		startcmparing(t_env *currentenv, t_expand *var);
void		dollar_herdoc_case(t_cmd	*currentcmd, t_expand	*var);
int			check_dolar(char *input);
void		exit_status_case(t_expand	*var);
void		expand_loop(t_env *envlist, t_cmd	*currentcmd, t_expand	*var);
void		expand_partone(t_cmd	*currentcmd,
				t_env	*envlist, t_expand	*var);
int			outappnd(t_shellcmd *current, int i);
int			error_quotation_after_symbole(t_shellcmd *current, int i);
int			check_redirection_cases(t_shellcmd *current, int i);
int			output_case(t_shellcmd	*current, int i);
int			input_case(t_shellcmd	*current, int i);
void		addback_filenode(t_file **head, t_file *newnode);
t_file		*create_filenode(char *filename);
void		herdoc_loop(t_shellcmd *list, char *tofind, \
t_expand	*var, t_env	*env);
t_shellcmd	*create_shellnode(char **command);
void		aplly_partone(t_shellcmd *list, char *input,
				t_expand *var, t_env *env);
void		controlc(int sig);
char		**step_one(t_cmd **command, t_env	*env, t_expand *var);
void		free_filelist(void);
void		step_two(t_shellcmd	**list);
void		step_three(t_shellcmd **list, t_env **env, char *input);
void		step_four(char **splitedcmd, t_shellcmd **list, t_cmd **command);
void		fixing_garbage_value(char **cmd);
void		free_finallist(t_shellcmd **command);
void		set_backnonvalidcommand(t_shellcmd *list);
void		signal_step(void);
void		ctrl_d(char *input);
int			emptyline_step(char *input);
int			syntaxerror_step(t_cmd **command, char *input);
int			redirection_step(t_env *env, t_shellcmd **list, \
t_expand	*var, char *input);
int			test_fail(t_cmd **command, char *input);
void		do_twosteps(t_shellcmd **list, t_env **env, char *input);

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

void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_echo(t_shellcmd *cmd);
int			ft_isalpha(int arg);
int			ft_isdigit(int arg);
int			ft_exit(t_shellcmd *cmd);
int			ft_atoi(char *str);
int			ft_printf(const char *str, ...);
int			ft_strncmp(const char *first, const char *second, size_t len);
void		ft_pwd(void);
char		*my_strjoin(char *s1, char *s2);
char		**ft_split(char *s, char c);
void		**ft_free(char **s);
void		ft_env(t_env *env, t_shellcmd *cmd);
void		ft_execution(t_shellcmd *cmd, t_env **shellenv );
int			ft_exec_builtins(t_shellcmd *cmd, t_env **env);
int			ft_chercher_builtins(t_shellcmd *cmd, t_env *env);
void		ft_exec_path(t_shellcmd *cmd, t_env *shellenv );
char		*git_path(t_env *env);
char		*ft_check_path(char **spl, char *cmd);
char		*ft_path(char **spl, char *cmd);
void		ft_cd(t_shellcmd *cmd, t_env **env);
void		change_pwd(t_shellcmd *cmd, t_env *env);
void		ft_oldpwd(t_env *env, char *str);
void		ft_unset(t_shellcmd *cmd, t_env **env);
void		ft_export(t_shellcmd *cmd, t_env **env);
int			ft_check_cmd(char *str);
void		add_cmd(t_env *env, t_shellcmd *cmd, int i, char **key);
void		ajouter_keyvaleur(t_env **env, char *str, char **key);
t_env		cree_node(char *key, char *value);
void		ft_add_liste(t_env *head, t_env *new_node);
int			modifier_env(t_env **env, char *command);
void		ft_creefork(char *s, t_shellcmd *cmd, char **newenv);
char		**ft_envirenment(t_env *shellenv);
int			countnodes(t_env *head);
void		sighandler(int sig);
void		ft_freearr(char **s);
int			ft_change_env(char **key, t_env *current, int flag);
int			ft_pipe(t_shellcmd *cmd, t_env **shellenv);
void		ft_getpath(t_shellcmd *cmd, t_env **shellenv);
void		pipe_exec_cmd(t_shellcmd *cmd, t_env **shellenv);
int			checkkeyexport(char *str);
char		**check_plusegal_cmd(t_env *current, char *command, int j);
void		cas_erreur(void);
void		addencas_env_null(t_env **env, char *command);
void		env_null(t_env **env);
void		ft_check_commande(t_shellcmd *cmd, t_env **shellenv);
void		suite_execution(t_shellcmd *cmd, t_env **shellenv);
void		handler_c(int signo);
void		ft_file(t_shellcmd *cmd, int pipfd[2]);
void		ft_close_fd(t_shellcmd *cmd, int pipfd[2]);
void		ft_directory(char *s, t_shellcmd *cmd, char **newenv);
void		ft_message_erreur(char *s1, char *s2, char *s3, int status);
void		ft_erreur_access(char *path, char *cmd);
void		ft_path_erreur(char *cmd);
char		*ft_home(t_shellcmd *cmd, t_env **env);
void		ft_pipe_erreur(void);
int			find(char *s);
void		direction(t_shellcmd *cmd, char *s, char **newenv);
void		ft_stat(char *command, t_shellcmd *cmd, char	**newenv);
int			exit_child(int status);
char		*ft_direction(t_shellcmd *cmd, char **newenv, t_env *shellenv);
void		ft_chercher(t_shellcmd *cmd, t_env **env, int j);
void		ft_change(t_env *current, char **key, char *new_value);
void		check_malloc(void *ptr);
void		dup_close(int tmp_fd_in, int tmp_fd_out);
void		handlequit(int sig);
void		ft_check_k(t_shellcmd *cmd);
void		suite_change(char **key, t_env *current, int flag);
void		ft_add(t_env *env, t_env	*tmp_env);
void		check_export(t_env	*current, char *command);
#endif
