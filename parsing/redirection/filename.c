/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:54:32 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/31 22:56:59 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_file	*create_filenode(char *filename)
{
	t_file	*node;

	node = ft_calloc(sizeof(t_file), 1);
	if (!node)
		return (NULL);
	node->filename = filename;
	node->next = NULL;
	return (node);
}
void	addback_filenode(t_file **head, t_file *newnode)
{
	t_file	*temp;

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