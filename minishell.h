/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:11:09 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/20 20:29:52 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char			**input;
	int				fd_input;
	int				fd_output;
	struct s_cmd	*next;
}	t_cmd;

int	ft_strlen(char *str);
void	ft_readline(char *input);
int		check_quotes(char *input);
void	syntaxerror(char *input);
int		is_whitespace(char c);
int		check_special(char c);
int		pipe_errors(char *input);
int		special_char_only(char *input);
char	**ft_split(char const *s, char c);
t_cmd	*create_node(char **splited_input);
t_cmd	*last_node(t_cmd	*node);
void	addback_node(t_cmd **head, t_cmd *newnode);
void	reset_inquotevalues(char	*command);
void	protect_inquote(char *input);
#endif