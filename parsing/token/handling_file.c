/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:39:25 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/08 23:00:16 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	whitespace_case(char *input, int *i, t_cmd	**head)
{
	t_cmd *node;

	node = NULL;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	node = create_node(" ", t_space);
	addback_node(head,node);
	
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

int	handle_singleq(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;
	int		j;
	char	*res;

	j = *i;
	if (check_quotes(input+(*i)))
	{
		printf("syntaxError : verify quotations\n");
		return (1);
	}
	if (input[j] == '\'')
	{
		j++;
		while(input[j] !='\'')
			j++;
	}
	res = ft_substr(input, ((*i) + 1) , j - (*i) - 1); 
	if (!res)
		return (1);
	node = create_node(res, t_singlequote);
	node->flag_var = 1;
	(*i) += j - (*i) + 1;
	addback_node(head, node);
	return (0);
}

int	handle_doubleq(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;
	int		j;
	char	*res;

	j = *i;
	if (check_quotes(input+(*i)))
	{
		printf("syntaxError : verify quotations\n");
		return (1);
	}
	if (input[j] == '\"')
	{
		j++;
		while(input[j] !='\"')
			j++;
	}
	res = ft_substr(input, ((*i) + 1) , j - (*i) - 1);
	if (!res)
		return (1);
	node = create_node(res, t_doublequote);
	node->flag_var = 2;
	(*i) += j - (*i) + 1;
	addback_node(head, node);
	return (0);
}

int	quotation_case(char *input, int *i, t_cmd **head)
{
	if (input[*i] == '\'')
	{
		if (handle_singleq(input, i, head) == 1)
			return (1);
	}
	else if (input[*i] == '\"')
	{
		if (handle_doubleq(input, i, head) == 1)
			return (1);
	}
	return (0);
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