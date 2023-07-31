/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:04:33 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/31 20:56:07 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char **ft_envirenment(t_env *shellenv)
{
	int cnt;
	int i;
	char **env;
	char *key;
	
	i = 0;
	cnt = countNodes(shellenv) + 1;
	env = (char **)calloc(cnt  , sizeof(char*));
	i = 0;
	while (shellenv->next != NULL && i < cnt)
	{
		key = ft_strjoin(shellenv->key, "=");
		env[i] = ft_strjoin(key , shellenv->value);
		free(key);
		i++;
		shellenv = shellenv->next;
	}
	return(env);
}

void sighandler(int sig)
{
	(void)sig;
	printf("^\\Quit:\n");
}

int countNodes(t_env *head) 
{
    int count = 0;
    t_env *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void	ft_freeArr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i++]);
	}
	free(s);
}

// while (current)
	// {
	// 	if(!ft_strncmp(key[0],current->key, ft_strlen(key[0]) + 1))
	// 	{
	// 		if(flag == 2 && key[1])
	// 		{
	// 			if (current->value == NULL)
	// 				current->value = ft_strdup("");
	// 			current->value = ft_strjoin(current->value, key[1]);
	// 		}
	// 		else
	// 			current->value = key[1];
	// 		flag = 1;
	// 	}
	// 	current = current->next;
	// }
	// if(flag == 1)
	// 	return(0);
	// ajouter_keyvaleur(*env, command, key);
	// return(1);