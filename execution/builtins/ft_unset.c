/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/29 15:25:16 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void ft_unset(t_shellcmd *cmd , t_env *env)
// {
// 	t_env *current;
// 	int j;
// 	char *s;
	
// 	j=1;
// 	while (cmd->command[j])
// 	{
// 		s = cmd->command[j];
// 		current = env;
// 		while (current && ft_strncmp(current->key, s, ft_strlen(current->key)))
// 		{
// 			current = current->next;
// 		}
// 		if(current)
// 		{
// 		// printf("{%s}\n", current->previous->key);
// 		// printf("{%s}\n", current->next->key);
// 			current->previous->next = current->next;
// 			free(current->key);
// 			free(current->value);
// 			free(current);
// 			// current->key = NULL;
// 			// current->value = NULL;
// 		}
// 		j++;
// 	}
// } 
void ft_unset(t_shellcmd *cmd, t_env **env) {
    t_env *current;
    int j;
    char *s;

    j = 1;
    while (cmd->command[j]) {
        s = cmd->command[j];
        current = *env;
        while (current && ft_strncmp(current->key, s, ft_strlen(current->key))) {
            current = current->next;
        }
        if (current) {
            if (current == *env) {
                // If the node to remove is the head
                (*env) = current->next;
                if (*env) {
                    (*env)->previous = NULL;
                }
            } else {
                // Update the previous node's next pointer
                if (current->previous) {
                    current->previous->next = current->next;
                }
            }

            // Update the next node's previous pointer
            if (current->next) {
				puts("check");
                current->next->previous = current->previous;
            }

            free(current->key);
            free(current->value);
            free(current);
        }
        j++;
    }
}

// void ft_unset(char *cmd , t_env *env)
// {
// 	char *temp;
// 	int i;
// 	t_env current;

// 	i = 0;
// 	current = env;
// 	while (current->next != NULL && cmd)
// 	{
// 		if(ft_strncmp(current.key , cmd, ft_strlen(current.key)))
// 		{
// 			if(current.previous == NULL);
// 		}
				
// 	}
	
// }
