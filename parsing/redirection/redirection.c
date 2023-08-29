/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:28:58 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/29 19:45:08 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_redirandfilename(char *command)
{
	int i = 0;
	while (command[i])
	{
		command[i] = '#';
		i++;
	}
}

char	**copy2(char **command)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	while (command[i])
		i++;
	tmp = ft_calloc(sizeof(char **), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (command[i])
	{
		if (command[i][0] != '#')
			tmp[j++] = ft_strdup(command[i]);
		i++;
	}
	return (tmp);
}

int	input_case(t_shellcmd	*current, int i)
{
	if (current->command[i + 1] && \
		current->command[i][0] == '<' && current->command[i][1] != '<')
	{
		if (current->fd_in != -2)
			close(current->fd_in);
		current->fd_in = open(current->command[i + 1], O_RDONLY);
		if (current->fd_in == -1)
		{
			current->error_flag = 1;
			perror("cuteshell :");
			return (1);
		}
		remove_redirandfilename(current->command[i]);
		remove_redirandfilename(current->command[i + 1]);
	}
	return (0);
}

int	output_case(t_shellcmd	*current, int i)
{
	if (current->command[i + 1] && current->command[i][0] == '>')
	{
		if (current->fd_out != -2)
			close(current->fd_out);
		current->fd_out = open(current->command[i + 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0666);
		remove_redirandfilename(current->command[i]);
		remove_redirandfilename(current->command[i + 1]);
		if (current->fd_out == -1)
		{
			current->error_flag = 1;
			perror("cuteshell ");
			return (1);
		}
	}
	return (0);
}

void	findredirection(t_env *env, t_shellcmd *command, t_expand	*var)
{
	t_shellcmd	*current;
	int			i;

	find_here_doc(env, command, var);
	current = command;
	while (current)
	{
		i = 0;
		while (current->command[i])
		{
			if (current->command[i][0] == '>' || \
			current->command[i][0] == '<' || (current->command[i][0] == '>' && \
			current->command[i][1] == '>'))
				if (check_redirection_cases(current, i) == 1)
					break ;
			i++;
		}
		current = current->next;
	}
	check_and_apply(command);
}
