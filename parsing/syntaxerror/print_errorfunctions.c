/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errorfunctions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:50:08 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/11 17:52:02 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

int	syntaxerror(t_cmd **list)
{
	t_cmd	*temp;

	temp = *list;
	while (temp)
	{
		if (temp->type == t_pipe || \
		temp->type == t_input || temp->type == t_output \
		|| temp->type == output_apnd || temp->type == here_doc)
			if (begin_end_oflist(temp))
				return (1);
		if (temp->type == t_pipe)
			if (pipe_error_firstcase(temp) || pipe_error_secondcase(temp))
				return (1);
		if (temp->type == t_input || \
			temp->type == t_output || temp->type == here_doc \
			|| temp->type == output_apnd)
			if (redirection_error(temp))
				return (1);
		temp = temp->next;
	}
	return (0);
}
