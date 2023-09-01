/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/01 17:41:44 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

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

void	ft_readline(char *input, t_cmd	**command, t_env *env, t_expand *var)
{
	char		**splitedcmd;
	t_shellcmd	**list;

	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, controlc);
		input = readline("Minishell$> ");
		if (input == NULL)
			exit (g_j.status_exit);
		if (verify_emptystring(input) == 1)
		{
			free(input);
			continue ;
		}
		add_history(input);
		command = tokenizer(input);
		if (!command)
		{
			free(input);
			continue ;
		}
		if (syntaxerror(command) == 1)
		{
			free_list(command);
			free(input);
			continue ;
		}
		splitedcmd = step_one(command, env, var);
		list = ft_calloc(sizeof(t_shellcmd *), 1);
		check_malloc(list);
		step_four(splitedcmd, list, command);
		if (findredirection(env,*list, var) == 1)
		{
			free_finallist(list);
			free_filelist();
			free(input);
			g_j.signal = 0;
			continue ;
		}
		step_two(list);
		step_three(list, &env, input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*env_list;
	t_cmd	*command;
	t_expand	var;

	(void)av;
	if ( ac > 1)
		return (printf("cuteshell: No such file or directory\n"), 1);
	char *tmp = malloc(0);
	if (!tmp)
		return (1);
	free(tmp);
	g_j.status_exit = 0;
	g_j.k = NULL;
	command = NULL;
	input = NULL;
	env_list = NULL;
	// if(!*env)
	// 	env_null(&env_list);
	// else
	creat_env_struct(env, &env_list);
	printf("\033[2J\033[1;1H");
	ft_readline(input, &command, env_list, &var);
	return (0);
}