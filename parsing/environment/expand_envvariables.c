/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envvariables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:23:05 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/22 18:25:42 by yochakib         ###   ########.fr       */
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
	var->start = 0;
	var->keytosearch = NULL;
	var->temp = NULL;
	var->input = NULL;
}

void	expand_partone(t_cmd	*currentcmd,t_env	*envlist,t_expand	*var)
{
	t_env	*currentenv;

	if (var->input[var->i] == '$' && (currentcmd->flag_var == 0 \
		|| currentcmd->flag_var == 2) \
		&& currentcmd->here_doc != 2)
	{
		var->i = var->i + 1;
		var->start = var->i;
		while (var->input[var->i] && ft_isalnum(var->input[var->i]))
			var->i++;
		var->end = var->i - 1;
		var->keytosearch = ft_substr(var->input, var->start, \
		(var->end - var->start + 1));
		currentenv = envlist;
		while (currentenv)
		{
			if (!ft_strcmp(currentenv->key, var->keytosearch))
			{
				while (currentenv->value[var->k])
					var->temp[var->j++] = currentenv->value[var->k++];
				break ;
			}
			currentenv = currentenv->next;
		}
			var->i -= 1;
	}
}

void	check_and_expand(t_env  *envlist, t_cmd *commandlist, t_expand	*var)
{
	t_cmd	*currentcmd;
	int		count;
	char	*tmp;

	init_expand(var);
	currentcmd = commandlist;
	count = 1;
	while (currentcmd)
	{
		var->input = ft_strdup(currentcmd->input);
		var->temp = ft_calloc(100000, 1); //needs modification
		if (!var->temp)
			return ;
		while (var->input[var->i])
		{
			var->k = 0;
			while (var->input[var->i] && var->input[var->i] != '$')
			{
				if (currentcmd->here_doc == 2 && count == 1 && \
					check_dolar(currentcmd->input))
				{
					var->temp[var->j++] = '$';
					count -= 1;
				}
				var->temp[var->j++] = var->input[var->i++];
			}
			if (var->input[var->i] == '$' && var->input[var->i + 1] == '?')
			{
				tmp = ft_itoa(status_exit);
				while (*tmp)
				{
					var->temp[var->j] = *tmp++;
					var->j++;
				}
				var->i++;
			}
			expand_partone(currentcmd, envlist, var);
			if (var->input[var->i])
				var->i++;
		}
		var->temp[var->j] = '\0';
		currentcmd->input = ft_strdup(var->temp);
		free(var->temp);
		var->i = 0;
		var->j = 0;
		currentcmd = currentcmd->next;
	}
}
