/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:39:25 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/22 18:11:39 by yochakib         ###   ########.fr       */
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

void	handle_singleq(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;
	int		j;
	char	*res;

	j = *i;
	if (input[j] == '\'')
	{
		j++;
		while(input[j] !='\'')
			j++;
	}
	res = ft_substr(input, ((*i) + 1) , j - (*i) - 1);
	// reset_inquotevalues(res);
	if (!res)
		return ;
	node = create_node(res, t_singlequote);
	(*i) += j - (*i) + 1;
	addback_node(head, node);
}

void	handle_doubleq(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;
	int		j;
	char	*res;

	j = *i;
	if (input[j] == '\"')
	{
		j++;
		while(input[j] !='\"')
			j++;
	}
	res = ft_substr(input, ((*i) + 1) , j - (*i) - 1);
	// reset_inquotevalues(res);
	if (!res)
		return ;
	node = create_node(res, t_doublequote);
	(*i) += j - (*i) + 1;
	addback_node(head, node);
}

void	quotation_case(char *input, int *i, t_cmd **head)
{
	if (input[*i] == '\'')
		handle_singleq(input, i, head);
	else if (input[*i] == '\"')
		handle_doubleq(input, i, head);
}

void	word_case(char *input, int *i, t_cmd **head)
{
	t_cmd *node;
	int j;
	char *res;

	j = *i;
	while (input[j] && input[j] != '|' && input[j] != '<'
		&& input[j] != '>' && input[j] != '\'' && input[j] != '\"'
		&& !is_whitespace(input[j]))
		j++;
	res = ft_substr(input, (*i), (j - (*i)));
	if (!res)
		return ;
	node = create_node(res, t_word);
	(*i) += j - (*i);
	addback_node(head, node);
}