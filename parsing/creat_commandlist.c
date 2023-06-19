/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_commandlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:24:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/19 18:08:37 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_node(char *splited_input)
{
	t_cmd	**node;

	(*node) = malloc(sizeof(t_cmd));
	if (*node)
		return (NULL);
	(*node)->input = splited_input;
	(*node)->fd_input = 0;
	(*node)->fd_output = 1;
	(*node)->next = NULL;
	return (*node);
}

t_cmd	*last_node(t_cmd	*node)
{
	while (node->next)
		node = node->next;
	return (node);
}

void	addback_node(t_cmd **head, t_cmd *newnode)
{
	t_cmd	*temp;

	temp = *head;
	if (!*head)
	{
		*head = newnode;
		return ;
	}
	last_node(temp)->next = newnode;
}
