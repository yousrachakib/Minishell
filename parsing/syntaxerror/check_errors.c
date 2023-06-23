/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:04:29 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/23 20:25:20 by yochakib         ###   ########.fr       */
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
		if (temp->next == NULL)
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		temp = temp->next;
	}
	temp = list;
	if (temp->type == t_pipe)
	{
		if (temp->previous == NULL)
		{
			printf("syntax error near unexpected token\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	syntaxerror(t_cmd **list)
{
	t_cmd *temp;

	temp = *list;
	while (temp)
	{
		if (temp->type == t_pipe || temp->type == t_input || temp->type == t_output \
		|| temp->type == output_apnd || temp->type == here_doc)
			if (begin_end_oflist(temp) == 1)
				return (1);	
		temp = temp->next;	
	}
	return (0);
}