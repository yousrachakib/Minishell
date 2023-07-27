/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_commandlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:24:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/27 15:38:48 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*create_node(char *splited_input, t_type type)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->input = splited_input;
	node->type = type;
	node->flag_var = 0;
	node->next = NULL;
	node->previous = NULL;
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
	while (temp->next)
		temp = temp->next;
	temp->next = newnode;
	newnode->previous = temp;
}
