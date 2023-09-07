/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lastnormfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:46:18 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/07 19:10:08 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	test_fail(t_cmd **command, char *input)
{
	if (!command)
	{
		free(input);
		return (1);
	}
	return (0);
}

void	step_two(t_shellcmd	**list)
{
	t_shellcmd	*tmp_list;
	int			i;

	tmp_list = *list;
	while (tmp_list)
	{
		i = 0;
		while (tmp_list->command[i++])
			fixing_garbage_value(tmp_list->command);
		tmp_list = tmp_list->next;
	}
}

void	step_four(char **splitedcmd, t_shellcmd **list, t_cmd **command)
{
	int			i;
	char		**splitedcmd2;

	i = 0;
	while (splitedcmd[i])
	{
		splitedcmd2 = ft_split(splitedcmd[i], ' ');
		addback_shellnode(list, create_shellnode(splitedcmd2));
		ft_freearr(splitedcmd2);
		i++;
	}
	free_list(command);
	ft_freearr(splitedcmd);
	set_backnonvalidcommand(*list);
}

void	ft_readline(char *input, t_cmd	**command, t_env *env, t_expand *var)
{
	char		**splitedcmd;
	t_shellcmd	**list;

	while (1)
	{
		rl_catch_signals = 0;
		signal_step();
		input = readline("Minishell$> ");
		ctrl_d(input);
		if (emptyline_step(input) == 1)
			continue ;
		add_history(input);
		command = tokenizer(input);
		if (test_fail(command, input) == 1)
			continue ;
		if (syntaxerror_step(command, input) == 1)
			continue ;
		splitedcmd = step_one(command, env, var);
		list = ft_calloc(sizeof(t_shellcmd *), 1);
		check_malloc(list);
		step_four(splitedcmd, list, command);
		if (redirection_step(env, list, var, input) == 1)
			continue ;
		do_twosteps(list, &env, input);
	}
}

void	check_and_apply(t_shellcmd *list)
{
	t_shellcmd	*tmp;
	char		**temp;

	tmp = list;
	while (tmp)
	{
		temp = copy2(tmp->command);
		ft_freearr(tmp->command);
		tmp->command = temp;
		tmp = tmp->next;
	}
}
