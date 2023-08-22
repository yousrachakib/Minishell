/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:24:57 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/22 18:00:03 by yochakib         ###   ########.fr       */
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

char    *here_doc_expand(t_env   *env, char *input, t_expand *var)
{
	t_env	*currentenv;

	init_expand(var);
	var->temp = ft_calloc(ft_strlen(input) + 1, 10000);
	if (!var->temp)
		return (NULL);
	while (input[var->i])
	{
		var->k = 0;
		while (input[var->i] && input[var->i] != '$')
			var->temp[var->j++] = input[var->i++];
		if (input[var->i] == '$')
		{
			var->i = var->i + 1;
			var->start = var->i;
			while (input[var->i] && ft_isalnum(input[var->i]))
				var->i++;
			var->end = var->i - 1;
			var->keytosearch = ft_substr(input, var->start, \
			(var->end - var->start + 1));
			currentenv = env;
			search(currentenv, var->keytosearch, var);
		var->i -= 1;
		}
		if (input[var->i] == '$' && input[var->i + 1] == '?')
			ft_putstr_fd(ft_itoa(status_exit), 1);
		if (input[var->i])
			var->i++;
	}
	return (var->temp);
}
