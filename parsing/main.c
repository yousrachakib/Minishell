/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/08/24 20:01:04 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
int status_exit;

void	check_and_apply(t_shellcmd *list)
{
	t_shellcmd	*tmp;
	char		**temp;

	tmp = list;
	while (tmp)
	{
		temp = copy2(tmp->command);
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

void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd **list, t_expand *var)
{
	char	*firstcommand;
	char	**splitedcmd;
	char	**splitedcmd2;

	while (1)
	{
		input = readline("cuteshell$> ");
		if (input == NULL)
			break ;
		if (verify_emptystring(input) == 1)
		{
			free(input);
			continue ;
		}
		if (input[0] != '\0')
			add_history(input);
		command = tokenizer(input);
		if (!command)
			continue ;
		if (syntaxerror(command) == 1) // free in case of error
			continue ;
		fill_heredoc_var(command);
		check_and_expand(final_list,(*command), var);
		firstcommand = join_commands((*command));
		splitedcmd = ft_split(firstcommand, '|');
		free(firstcommand);
		set_nonvalidcommand(splitedcmd);
		int i = 0;
		while (splitedcmd[i])
		{
			splitedcmd2 = ft_split(splitedcmd[i], ' '); // free after
			addback_shellnode(list, create_shellnode(splitedcmd2));
			i++;
		}
		set_backnonvalidcommand(*list);
		findredirection(final_list,*list, var);
		t_shellcmd *tmp_list = *list;
		while (tmp_list)
		{
			i = 0;
			while (tmp_list->command[i])
			{
				
				printf("****%s******\n", tmp_list->command[i++]);
				printf("==>>|%d|\n", tmp_list->fd_in);
			}
			printf("next -->> %p\n", tmp_list->next);
			tmp_list = tmp_list->next;
		}
		tmp_list = *list;
		ft_execution(tmp_list, &final_list);
		*list = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*env_list;
	t_cmd	*command;
	t_shellcmd	*finallist;
	t_expand	var;

	(void)ac;
	(void)av;
	status_exit = 0;
	finallist = NULL;
	command = NULL;
	input = NULL;
	env_list = NULL;
	// if(!*env)
	// 	env_null(&env_list);
	// else
	creat_env_struct(env, &env_list);
	printf("\033[2J\033[1;1H");
	ft_readline(input, &command, env_list, &finallist, &var);
	return (0);
}
