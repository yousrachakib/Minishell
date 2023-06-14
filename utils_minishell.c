/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:40:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/14 10:45:47 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_node(t_cmd	*node)
{
	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	return (node);
}

void	addback_node(t_cmd **head, t_cmd *newnode)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = newnode;
		return ;
	}
	while (tmp)
		tmp = tmp->next;
	tmp->next = newnode;
	newnode->next = *head;
}