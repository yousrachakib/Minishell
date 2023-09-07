/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:39:25 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/07 18:52:33 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	whitespace_case(char *input, int *i, t_cmd	**head)
{
	t_cmd	*node;

	node = NULL;
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	node = create_node(ft_strdup(" "), t_space);
	addback_node(head, node);
}

t_cmd	*caseone(int *i, char *input)
{
	t_cmd	*node;

	node = NULL;
	if (input[*i + 1] == '<')
	{
		node = create_node(ft_strdup("<<"), here_doc);
		node->here_doc = 1;
		(*i)++;
	}
	else
		node = create_node(ft_strdup("<"), t_input);
	return (node);
}

void	separators_case(char *input, int *i, t_cmd **head)
{
	t_cmd	*node;

	node = NULL;
	if (input[*i] == '|')
		node = create_node(ft_strdup("|"), t_pipe);
	else if (input[*i] == '<')
		node = caseone(i, input);
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			node = create_node(ft_strdup(">>"), output_apnd);
			(*i)++;
		}
		else
			node = create_node(ft_strdup(">"), t_output);
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
	if (check_quotes(input + (*i)))
	{
		ft_putstr_fd("syntaxError : verify quotations\n", 2);
		return (1);
	}
	else if (input[j] && input[j] == '\'' && input[j + 1] && input[j + 1] == '\'' )
	{
        res = ft_strdup(" \'\'");
        node = create_node(ft_strdup(res), t_doublequote);
        free(res);
        node->flag_var = 2;
        (*i) = j + 2;
        addback_node(head, node);
        return(0);
    }
	if (input[j] == '\'')
	{
		j++;
		while (input[j] != '\'')
			j++;
	}
	res = ft_substr(input, ((*i) + 1), j - (*i) - 1);
	if (!res)
		return (1);
	node = create_node(ft_strdup(res), t_singlequote);
	free(res);
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
	if (check_quotes(input + (*i)))
	{
		ft_putstr_fd("syntaxError : verify quotations\n", 2);
		return (1);
	}
	// else if (input[j] && input[j] == '\"' && input[j + 1] && input[j + 1] == '\"' )
	// {
    //     res = ft_strdup(" \"\"");
    //     node = create_node(ft_strdup(res), t_doublequote);
    //     free(res);
    //     node->flag_var = 2;
    //     (*i) = j + 2;
    //     addback_node(head, node);
    //     return(0);
    // }
	if (input[j] == '\"')
	{
		j++;
		while (input[j] != '\"')
			j++;
	}
	res = ft_substr(input, ((*i) + 1), j - (*i) - 1);
	if (!res)
		return (1);
	node = create_node(ft_strdup(res), t_doublequote);
	free(res);
	node->flag_var = 2;
	(*i) += j - (*i) + 1;
	addback_node(head, node);
	return (0);
}
