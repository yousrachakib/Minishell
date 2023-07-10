/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:04:29 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/08 23:18:04 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	begin_end_oflist(t_cmd *list)
{
	t_cmd *temp;

	temp = list;
	if (temp->type == t_pipe || temp->type == t_input || temp->type == t_output \
		|| temp->type == output_apnd || temp->type == here_doc)
	{
		if (temp->next)
		{
			if (temp->next->type == t_space)
				temp = temp->next;
		}
		if (temp->next == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			status_exit = 258;
			return (1);
		}
	}
	temp = list;
	if (temp->type == t_pipe)
	{
		if (temp->previous)
		{
			if (temp->previous->type == t_space)
				temp = temp->previous;
		}
		if (temp->previous == NULL)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			status_exit = 258;
			return (1);
		}
	}
	return (0);
}

int	pipe_error_secondcase(t_cmd *list)
{
	t_cmd *temp;

	temp = list;
	if (temp->previous->type == t_space)
		temp = temp->previous;
	if (temp->previous->type == t_word || temp->previous->type == t_singlequote || \
		temp->previous->type == t_doublequote )
		return (0);
	else
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		status_exit = 258;
	}
	return (1);
}
int	pipe_error_firstcase(t_cmd *list)
{
	t_cmd *temp;

	temp = list;
	if (temp->next->type == t_space)
		temp = temp->next;
	if (temp->next->type == t_pipe)
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		status_exit = 258;
		return (1);
	}
	return (0);
}

int redirection_error(t_cmd *list)
{
	t_cmd *temp;

	temp = list;
	if (temp->next->type == t_space)
		temp = temp->next;
	if (temp->next->type == t_word || temp->next->type == t_singlequote \
		 || temp->next->type == t_doublequote)
		return (0);
	else
	{
		ft_putstr_fd("syntax error near unexpected token\n", 2);
		status_exit = 258;
	}
	return (1);
}

int	syntaxerror(t_cmd **list)
{
	t_cmd *temp;

	temp = *list;
	while (temp)
	{
		if (temp->type == t_pipe || temp->type == t_input || temp->type == t_output \
		|| temp->type == output_apnd || temp->type == here_doc)
			if (begin_end_oflist(temp))
				return (1);
		if (temp->type == t_pipe)
			if (pipe_error_firstcase(temp) || pipe_error_secondcase(temp))
				return (1);
		if (temp->type == t_input || temp->type == t_output || temp->type == here_doc \
			|| temp->type == output_apnd)
			if (redirection_error(temp))
				return (1);
		temp = temp->next;	
	}
	return (0);
}