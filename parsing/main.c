/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/28 17:17:46 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int status_exit;

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
		// ft_freearr(temp);
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
	int k = -1;
	while (cmd[++k])
	{
		int kk= -1;
		while (cmd[k][++kk])
			if(cmd[k][kk] < 0)
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
		
		// if (next->command && next->command[0])
			ft_freearr(next->command);
		if(next)
			free(next);
		next = NULL;
	}
	free(command);
	command = NULL;
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
}
void	ft_readline(char *input, t_cmd	**command, t_env *env, t_expand *var)
{
	char	*firstcommand;
	char	**splitedcmd;
	char	**splitedcmd2;
	t_shellcmd **list;
	
	rl_catch_signals = 0;
	while (1)
	{
		list = ft_calloc(sizeof(t_shellcmd *), 1);
		if (!list)
			return ;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, controlc);
		input = readline("cuteshell$> ");
		if (input == NULL)
			exit (status_exit);
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
		fill_heredoc_var(command);
		check_and_expand(env,(*command), var);
		firstcommand = join_commands((*command));
		splitedcmd = ft_split(firstcommand, '|');
		fixing_garbage_value(splitedcmd);
		set_nonvalidcommand(splitedcmd);
		free(firstcommand);
		firstcommand = NULL;
		int i = 0;
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
		findredirection(env,*list, var);
		t_shellcmd *tmp_list = *list;
		while (tmp_list)
		{
			i = 0;
			while (tmp_list->command[i])
				printf("|%s|\n", tmp_list->command[i++]);
			tmp_list = tmp_list->next;
		}
		tmp_list = *list;
		ft_execution(tmp_list, &env);
		free_finallist(list);
		// *list = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*env_list;
	t_cmd	*command;
	t_expand	var;

	(void)ac;
	(void)av;
	status_exit = 0;
	command = NULL;
	input = NULL;
	env_list = NULL;
	// if(!*env)
	// 	env_null(&env_list);
	// else
	creat_env_struct(env, &env_list);
	// printf("\033[2J\033[1;1H");
	ft_readline(input, &command, env_list, &var);
	return (0);
}
