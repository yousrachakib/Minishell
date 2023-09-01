/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:00:51 by mben-sal          #+#    #+#             */
/*   Updated: 2023/09/01 20:45:53 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**check_plusegal_cmd(t_env *current, char *command, int j)
{
	char	**key;

	key = (char **)ft_calloc(3, sizeof(char *));
	check_malloc(key);
	if (current->flag == 2)
	{
		key[0] = ft_substr(command, 0, j);
		key[1] = ft_substr(command, j + 2, (ft_strlen(command) - j));
	}
	else if (current->flag != 2)
		key[0] = ft_substr(command, 0, j);
	if (command[j] == '=' && current->flag != 2)
		key[1] = ft_substr(command, j + 1, (ft_strlen(command) - j));
	else if (command[j] == '\0')
	{
		key[1] = NULL;
		if (current->flag != 3)
			current->flag = 0;
	}
	return (key);
}

int	ft_change_env(char **key, t_env *current, int flag)
{
	while (current)
	{
		if (!ft_strncmp(key[0], current->key, ft_strlen(key[0]) + 1))
		{
			suite_change(key, current, flag);
			flag = 1;
			free(key);
			break ;
		}
		current = current->next;
	}
	return (flag);
}

void	ft_change(t_env *current, char **key, char *new_value)
{
	if (current->value == NULL)
		current->value = ft_strdup("");
	new_value = ft_strjoin(current->value, key[1]);
	free(key[1]);
	current->value = new_value;
	free(key[0]);
}

void	suite_change(char **key, t_env *current, int flag)
{
	char	*new_value;

	if (flag == 2 && key[1])
	{
		new_value = NULL;
		ft_change(current, key, new_value);
	}
	else
	{
		if (flag != 3)
			free(current->value);
		if (flag != 3)
			current->value = key[1];
		free(key[0]);
	}
}
