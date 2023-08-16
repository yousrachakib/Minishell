/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:07:37 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/16 19:26:18 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*creat_filename(void)
{
	int		num;
	char	*name;
	char	*name2;

	num = random();
	name = ft_itoa(num);
	name2 = ft_strjoin(ft_strdup("/tmp/temp"), name);
	free(name);
	return (name2);
}

void	handle_heredoc(t_env *env, char *tofind, t_expand *var)
{
	int		fd;
	char	*input;
	char	*temp;
	char	*filename;

	filename = creat_filename();
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		ft_putstr_fd("Error file not found", 2);
	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, tofind) != 0)
		{
			temp = here_doc_expand(env, input, var);
			free(input);
			input = temp;
			ft_putstr_fd(input, fd);
			ft_putstr_fd("\n", fd);
			free(input);
		}
		else
			break ;
	}
}

void	find_here_doc(t_env *env, t_shellcmd *list, t_expand *var)
{
	t_shellcmd	*temp;
	int			i;

	temp = list;
	while (temp)
	{
		i = 0;
		while (temp->command[i])
		{
			if (temp->command[i][0] == '<' && temp->command[i][1] == '<')
				handle_heredoc(env, temp->command[i + 1], var);
			i++;
		}
		temp = temp->next;
	}
}
