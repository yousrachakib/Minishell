/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:25:27 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/02 16:05:39 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_malloc(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("Malloc ERROR\n", 2);
		exit(1);
	}
}

void	controlc(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_j.status_exit = 1;
}

void	free_filelist(void)
{
	t_file	*next;
	t_file	*tmp;

	tmp = g_j.k;
	while (tmp)
	{
		next = tmp;
		tmp = tmp->next;
		unlink(next->filename);
		free(next->filename);
		if (next)
			free(next);
		next = NULL;
	}
	g_j.k = NULL;
}

char	**step_one(t_cmd **command, t_env	*env, t_expand *var)
{
	char	*firstcommand;
	char	**splitedcmd;

	fill_heredoc_var(command);
	check_and_expand(env, (*command), var);
	firstcommand = join_commands((*command));
	splitedcmd = ft_split(firstcommand, '|');
	set_nonvalidcommand(splitedcmd);
	free(firstcommand);
	return (splitedcmd);
}

void	step_three(t_shellcmd **list, t_env **env, char *input)
{
	t_shellcmd	*tmp_list;

	tmp_list = *list;
	ft_execution(tmp_list, env);
	free_finallist(list);
	free_filelist();
	free(input);
}
