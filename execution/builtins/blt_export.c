/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:00:51 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/13 16:54:29 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**check_plusegal_cmd(t_env *current, char *command, int j)
{
	char	**key;

	key = (char **)calloc(3, sizeof(char *));
	if (!key)
		return (0);
	key[2] = NULL;
	if (current->flag == 2)
	{
		key[0] = ft_substr(command, 0, j);
		key[1] = ft_substr(command, j + 2, (ft_strlen(command) - j));
	}
	else if (current->flag != 2)
		key[0] = ft_substr(command, 0, j);
	if (command[j] == '=' && current->flag != 2)
		key[1] = ft_substr(command, j + 1, (ft_strlen(command) - j));
	if (command[j] == '=' && command[j + 1] == '\0')
		key[1] = ft_strdup("");
	else if (command[j] == '\0')
	{
		key[1] = NULL;
		current->flag = 0;
	}
	return (key);
}

int	ft_change_env(char **key, t_env *current, int flag)
{
	char *new_value;
	
	while (current)
	{
		if (!ft_strncmp(key[0], current->key, ft_strlen(key[0]) + 1))
		{
			if (flag == 2 && key[1])
			{

				new_value = NULL;
				if (current->value == NULL)
					current->value = ft_strdup("");
				new_value = ft_strjoin(current->value, key[1]);
				current->value = new_value;
			}
			else
			{
				current->value = key[1];
			}
			flag = 1;
		}
		current = current->next;
	}
	return (flag);
}
