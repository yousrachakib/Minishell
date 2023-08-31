/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normienv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:44:54 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/31 19:22:29 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	startcmparing(t_env *currentenv, t_expand *var)
{
	while (currentenv)
	{
		if (currentenv->key && var->keytosearch && \
		!ft_strcmp(currentenv->key, var->keytosearch))
		{
			while (currentenv->value && currentenv->value[var->k])
				var->temp[var->j++] = currentenv->value[var->k++];
			break ;
		}
		currentenv = currentenv->next;
	}
}

void	dollar_herdoc_case(t_cmd	*currentcmd, t_expand	*var)
{
	while (var->input[var->i] && var->input[var->i] != '$')
	{
		if (currentcmd->here_doc == 2 && var->count == 1 && \
			check_dolar(currentcmd->input))
		{
			var->temp[var->j++] = '$';
			var->count -= 1;
		}
		var->temp[var->j++] = var->input[var->i++];
	}
}

void	exit_status_case(t_expand	*var)
{
	char	*tmp;
	int		indx;

	if (var->input && var->input[var->i] == '$' && var->input[var->i + 1] \
	&& var->input[var->i + 1] == '?')
	{
		tmp = ft_itoa(g_j.status_exit);
		if (!tmp)
			exit(1);
		indx = 0;
		while (tmp[indx])
			var->temp[var->j++] = tmp[indx++];
		if (tmp)
			free(tmp);
		tmp = NULL;
		var->i++;
	}
}

void	expand_partone(t_cmd	*currentcmd, t_env	*envlist, t_expand	*var)
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
		startcmparing(currentenv, var);
		if (var->keytosearch)
			free(var->keytosearch);
		var->keytosearch = NULL;
		var->i -= 1;
	}
}

void	expand_loop(t_env *envlist, t_cmd	*currentcmd, t_expand	*var)
{
	while (var->input[var->i])
	{
		var->k = 0;
		dollar_herdoc_case(currentcmd, var);
		exit_status_case(var);
		expand_partone(currentcmd, envlist, var);
		if (var->input[var->i])
			var->i++;
	}
}
