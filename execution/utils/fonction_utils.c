/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:04:33 by mben-sal          #+#    #+#             */
/*   Updated: 2023/08/21 18:48:58 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_envirenment(t_env *shellenv)
{
	int		cnt;
	int		i;
	char	**env;
	char	*key;

	i = 0;
	cnt = countnodes (shellenv) + 1;
	if (cnt <= 1)
		return (NULL);
	env = (char **)ft_calloc(cnt, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (shellenv->next != NULL && i < cnt)
	{
		key = ft_strjoin(shellenv->key, "=");
		env[i] = ft_strjoin(key, shellenv->value);
		free(key);
		i++;
		shellenv = shellenv->next;
	}
	return (env);
}

void	sighandler(int sig)
{
	(void)sig;
	printf("^\\Quit:\n");
}

int	countnodes(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	ft_freearr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i++]);
	}
	free(s);
}

void	ft_erreur_access(char *path, char *cmd )
{
	ft_message_erreur("minishell :", cmd + 1, " :command not found \n");
	status_exit = 126;
	free(cmd);
	free(path);
}
