/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:07:37 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/07 18:45:56 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*creat_filename(void)
{
	static int		num;
	char			*name;
	char			*num_num;

	num_num = ft_itoa(++num);
	name = ft_strjoin(ft_strdup("/tmp/tmpy"), num_num);
	if (access(name, F_OK) == 0)
	{
		addback_filenode(&g_j.k, create_filenode(ft_strdup(name)));
		return (free(num_num), name);
	}
	else
	{
		free(name);
		free(num_num);
		num_num = ft_itoa(++num);
		name = ft_strjoin(ft_strdup("/tmp/tmpy"), num_num);
		addback_filenode(&g_j.k, create_filenode(ft_strdup(name)));
		return (free(num_num), name);
	}
}

void	aplly_partone(t_shellcmd *list, char *input, t_expand *var, t_env *env)
{
	char	*temp;

	temp = here_doc_expand(env, input, var);
	free(input);
	input = temp;
	ft_putstr_fd(input, list->fd_in);
	ft_putstr_fd("\n", list->fd_in);
	free(input);
}

void	signalher(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\4");
	g_j.signal = 1;
	g_j.status_exit = 1;
}

int	handle_heredoc(t_env *env, t_shellcmd *list, \
char *tofind, t_expand *var)
{
	char	*filename;

	filename = creat_filename();
	if (list->fd_in != -2)
		close(list->fd_in);
	list->fd_in = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (list->fd_in == -1)
		return (ft_putstr_fd("Error file not found", 2), free(filename), 2);
	signal(SIGINT, signalher);
	herdoc_loop(list, tofind, var, env); 
	if (g_j.signal == 1)
		return (close(list->fd_in), free(filename), 1);
	close(list->fd_in);
	if (list->fd_in != -2)
		close(list->fd_in);
	list->fd_in = open(filename, O_RDONLY, 0644);
	if (list->fd_in == -1)
		return (ft_putstr_fd("Error file not found", 2), free(filename), 2);
	return (free(filename), 0);
}

int	find_here_doc(t_env *env, t_shellcmd *list, t_expand *var)
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
				if (handle_heredoc(env, list, temp->command[i + 1], var) == 1)
					return (1);
				remove_redirandfilename(temp->command[i]);
				remove_redirandfilename(temp->command[i + 1]);
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
