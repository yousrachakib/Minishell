/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:18:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/02 21:06:32 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

t_env	*create_envnode(char *key, char *value)
{
	t_env	*node;
    
	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->previous = NULL;
	return (node);
}

void	addback_envnode(t_env **head, t_env *newnode)
{
	t_env	*temp;

	temp = *head;
	if (!(*head))
	{
		*head = newnode;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = newnode;
	newnode->previous = temp;
}

char    *retrieve_key(char *line)
{
    // int line_len;
    char *equal_sign;
    int key_len;
    char *key;

    // line_len = ft_strlen(line);
    equal_sign = ft_strchr(line, '=');
    if (!equal_sign)
        return NULL;
    key_len = equal_sign - line;
    key = ft_calloc(key_len + 1, 1);
    if (!key)
        return NULL;
    ft_strncpy(key, line, key_len);
    key[key_len] = '\0';
    return (key);
}

char *retrieve_value(char *line) 
{
    // int line_len;
	char *equal_sign;
	int key_len;
	char *key;
	char *value;
	char *value_duplicate;
	char *newline;

	// line_len = ft_strlen(line);
    equal_sign = ft_strchr(line, '=');
    key_len = equal_sign - line;
    key = ft_calloc(key_len + 1, 1);
    if (!key)
        return NULL;
    ft_strncpy(key, line, key_len);
    key[key_len] = '\0';
    value = equal_sign + 1;
    value_duplicate = ft_strdup(value);
    if (!value_duplicate) 
	{
        free(key);
        return NULL;
    }
    newline = ft_strchr(value_duplicate, '\n');
    if (newline)
        *newline = '\0';
    free(key);
    return (value_duplicate);
}
