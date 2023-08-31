/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:24:57 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/31 23:48:09 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	search(t_env	*currentenv, char *keytosearch, t_expand *var)
{
	while (currentenv)
	{
		if (!ft_strcmp(currentenv->key, keytosearch))
		{
			while (currentenv->value[var->k])
				var->temp[var->j++] = currentenv->value[var->k++];
			break ;
		}
		currentenv = currentenv->next;
	}
}

void	check_one(t_expand	*var, t_env	*env)
{
	t_env	*currentenv;

	if (var->input[var->i] == '$')
	{
		var->i = var->i + 1;
		var->start = var->i;
		while (var->input[var->i] && ft_isalnum(var->input[var->i]))
			var->i++;
		var->end = var->i - 1;
		var->keytosearch = ft_substr(var->input, var->start, \
			(var->end - var->start + 1));
		currentenv = env;
		search(currentenv, var->keytosearch, var);
		var->i -= 1;
	}
}

char	*here_doc_expand(t_env *env, char *input, t_expand *var)
{
	init_expand(var);
	var->temp = ft_calloc(ft_strlen(input) + 1, 10000);
	check_malloc(var->temp);
	var->input = ft_strdup(input);
	check_malloc(var->input);
	while (input[var->i])
	{
		var->k = 0;
		while (var->input[var->i] && var->input[var->i] != '$')
			var->temp[var->j++] = var->input[var->i++];
		check_one(var, env);
		exit_status_case(var);
		if (var->input[var->i])
			var->i++;
	}
	return (var->temp);
}
