/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:18:52 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/05 17:26:17 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_envnode(char *key, char *value)
{
	t_env	*node;
    
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->previous = NULL;
    puts("hi1");
	return (node);
}
void	addback_envnode(t_env **head, t_env *newnode)
{
	t_env	*temp;

	temp = *head;
	if (!*head)
	{
		*head = newnode;
		return ;
    puts("hi55");
	}
	while (temp)
		temp = temp->next;
	temp->next = newnode;
	newnode->previous = temp;
}

char    *retrieve_key(char *line)
{
    int line_len;
    char *equal_sign;
    int key_len;
    char *key;

    line_len = ft_strlen(line);
    equal_sign = ft_strchr(line, '=');
    if (!equal_sign)
        return NULL;
    key_len = equal_sign - line;
    key = malloc(key_len + 1);
    if (!key)
        return NULL;
    ft_strncpy(key, line, key_len);
    key[key_len] = '\0';
    puts("hi3");
    return (key);
}

char *retrieve_value(char *line) 
{
    int line_len;
	char *equal_sign;
	int key_len;
	char *key;
	char *value;
	char *value_duplicate;
	char *newline;

	line_len = ft_strlen(line);
    equal_sign = ft_strchr(line, '=');
    if (!equal_sign)
        return NULL;
    key_len = equal_sign - line;
    key = malloc(key_len + 1);
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
    puts("hi4");
    return (value_duplicate);
}
