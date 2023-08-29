/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvariables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:23:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/29 13:32:20 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_dolar(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	fill_heredoc_var(t_cmd	**command)
{
	t_cmd	*tmp;

	tmp = (*command);
	while (tmp)
	{
		if (tmp->here_doc == 1)
		{
			while (tmp->next->type == t_space)
				tmp = tmp->next;
			tmp->next->here_doc = 2;
		}
		tmp = tmp->next;
	}
}

void	init_expand(t_expand	*var)
{
	var->end = 0;
	var->i = 0;
	var->j = 0;
	var->k = 0;
	var->count = 1;
	var->start = 0;
	var->keytosearch = NULL;
	var->temp = NULL;
	var->input = NULL;
}

void	free_expandstruct(t_expand	*var)
{
	if (var->input)
		free(var->input);
	var->input = NULL;
	if (var->keytosearch)
		free(var->keytosearch);
	var->keytosearch = NULL;
	if (var->temp)
		free(var->temp);
	var->temp = NULL;
}

void	check_and_expand(t_env *envlist, t_cmd *commandlist, t_expand	*var)
{
	t_cmd	*currentcmd;

	init_expand(var);
	currentcmd = commandlist;
	while (currentcmd)
	{
		var->input = ft_strdup(currentcmd->input);
		var->temp = ft_calloc(100000, 1);
		if (!var->temp)
			return ;
		expand_loop(envlist, currentcmd, var);
		free(currentcmd->input);
		currentcmd->input = NULL;
		if (currentcmd->flag_var == 1)
			currentcmd->input = ft_strdup(var->input);
		else
			currentcmd->input = ft_strdup(var->temp);
		free_expandstruct(var);
		var->i = 0;
		var->j = 0;
		currentcmd = currentcmd->next;
	}
}
