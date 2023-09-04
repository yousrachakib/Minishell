/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normredirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:26:46 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/04 13:28:54 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	outappnd_case(t_shellcmd *current, int i)
{
	if ((current->command[i + 1] && current->command[i][0] == '>' \
		&& current->command[i][1] == '>'))
	{
		if (current->fd_out != -2)
			close(current->fd_out);
		current->fd_out = open(current->command[i + 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0666);
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

int	check_redirection_cases(t_shellcmd *current, int i)
{
	if (input_case(current, i) == 1)
		return (1);
	if (outappnd_case(current, i) == 1)
		return (1);
	if (output_case(current, i) == 1)
		return (1);
	return (0);
}

void	herdoc_loop(t_shellcmd *list, char *tofind, \
t_expand *var, t_env	*env)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (input && tofind && ft_strcmp(input, tofind) != 0)
			aplly_partone(list, input, var, env);
		else
		{
			free(input);
			break ;
		}
	}
}
