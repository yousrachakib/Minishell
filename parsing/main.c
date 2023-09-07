/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/07 19:07:29 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_backnonvalidcommand(t_shellcmd *list)
{
	int			i;
	t_shellcmd	*tmp_list;

	tmp_list = list;
	while (tmp_list)
	{
		i = 0;
		while (tmp_list->command[i])
		{
			if (tmp_list->command[i][0] < 0)
				protect_dumbquote(tmp_list->command[i]);
			i++;
		}
		tmp_list = tmp_list->next;
	}
}

void	fixing_garbage_value(char **cmd)
{
	int	k;
	int	kk;

	k = -1;
	while (cmd[++k])
	{
		kk = -1;
		while (cmd[k][++kk])
			if (cmd[k][kk] < 0)
				cmd[k][kk] *= -1;
	}
}

void	free_list(t_cmd **command)
{
	t_cmd	*next;
	t_cmd	*tmp;

	tmp = *command;
	while (tmp)
	{
		next = tmp;
		tmp = tmp->next;
		if (next->input)
			free(next->input);
		next->input = NULL;
		free(next);
	}
	free(command);
	command = NULL;
}

void	free_finallist(t_shellcmd **command)
{
	t_shellcmd	*next;
	t_shellcmd	*tmp;

	tmp = *command;
	while (tmp)
	{
		next = tmp;
		tmp = tmp->next;
		ft_freearr(next->command);
		if (next)
			free(next);
		next = NULL;
	}
	free(command);
	command = NULL;
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*env_list;
	t_cmd		*command;
	t_expand	var;
	char		*tmp;

	(void)av;
	if (ac > 1 || isatty(STDIN_FILENO) == 0)
		return (ft_putstr_fd("Minishell: No such file or directory\n", 2), 1);
	tmp = malloc(0);
	if (!tmp)
		return (1);
	free(tmp);
	g_j.status_exit = 0;
	g_j.k = NULL;
	command = NULL;
	input = NULL;
	env_list = NULL;
	creat_env_struct(env, &env_list);
	printf("\033[2J\033[1;1H");
	ft_readline(input, &command, env_list, &var);
	return (0);
}
