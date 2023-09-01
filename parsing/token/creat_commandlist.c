/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_commandlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:24:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/01 19:51:25 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*create_node(char *splited_input, t_type type)
{
	t_cmd	*node;

	node = ft_calloc(sizeof(t_cmd), 1);
	check_malloc(node);
	node->input = splited_input;
	node->type = type;
	node->flag_var = 0;
	node->here_doc = 0;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

t_shellcmd	*create_shellnode(char **command)
{
	t_shellcmd	*node;
	int			i;

	i = 0;
	node = ft_calloc(sizeof(t_shellcmd), 1);
	check_malloc(node);
	while (command[i])
		i++;
	node->command = ft_calloc((i + 1), sizeof(char *));
	check_malloc(node->command);
	i = 0;
	while (command[i])
	{
		node->command[i] = ft_strdup(command[i]);
		i++;
	}
	node->fd_in = -2;
	node->fd_out = -2;
	node->error_flag = 0;
	node->next = NULL;
	return (node);
}

void	addback_shellnode(t_shellcmd **head, t_shellcmd *newnode)
{
	t_shellcmd	*temp;

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
