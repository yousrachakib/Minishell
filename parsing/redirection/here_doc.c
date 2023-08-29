/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:07:37 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/29 18:50:22 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*creat_filename(void)
{
	int		num;
	char	*name;
	char	*name2;

	num = random();
	name = ft_itoa(num);
	name2 = ft_strjoin(ft_strdup("/tmp/temp"), name);
	free(name);
	return (name2);
}

void	handle_heredoc(t_env *env, t_shellcmd *list, char *tofind, t_expand *var)
{
	char	*input;
	char	*temp;
	char	*filename;

	filename = creat_filename();
	if (list->fd_out != -2)
		close(list->fd_out);
	list->fd_in = open(filename, O_WRONLY | O_CREAT, 0777);
	if (list->fd_in == -1)
		ft_putstr_fd("Error file not found", 2);
	while (1)
	{
		input = readline(">");
		if (input && tofind && ft_strcmp(input, tofind) != 0)
		{
			temp = here_doc_expand(env, input, var);
			free(input);
			input = temp;
			ft_putstr_fd(input, list->fd_in);
			printf(">>>>>%s<<<<<<\n", input);
			ft_putstr_fd("\n", list->fd_in);
			free(input);
		}
		else
		{
			free(input);
			break ;
		}
	}
	close(list->fd_in);
	list->fd_in = open(filename, O_RDONLY, 0644);
	if (list->fd_in == -1)
		ft_putstr_fd("Error file not found", 2);
	free(filename);
}

void	find_here_doc(t_env *env, t_shellcmd *list, t_expand *var)
{
	t_shellcmd	*temp;
	int			i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->command[i])
		{
			if (temp->command[i][0] == '<' && \
			temp->command[i][1] == '<' && temp->command[i + 1])
			{
				handle_heredoc(env, list, temp->command[i + 1], var);
				remove_redirandfilename(temp->command[i]);
				remove_redirandfilename(temp->command[i + 1]);
			}
			i++;
		}
		temp = temp->next;
	}
}
