/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:39:25 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/22 16:04:23 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	whitespace_case(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
}
void	separators_case(char *input, int *i, t_cmd **head)
{
	t_cmd *node;

	node = NULL;
	if (input[*i] == '|')
		node = create_node("|" , t_pipe);
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			node = create_node("<<" , here_doc);
			(*i)++;
		}
		else
			node = create_node("<", t_input);
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			node = create_node(">>" , output_apnd);
			(*i)++;
		}
		else
			node = create_node(">", t_output);
	}
	addback_node(head, node);
	(*i)++;
}