/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_commandlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:24:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/19 20:54:30 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*create_node(char **splited_input)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->input = splited_input;
	node->fd_input = 0;
	node->fd_output = 1;
	node->next = NULL;
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
}
