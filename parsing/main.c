/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/30 22:39:34 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_and_apply(t_shellcmd *list)
{
	t_shellcmd *tmp;
	char **temp;
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
	int i;
	t_shellcmd *tmp_list = list;
	while(tmp_list)
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
void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd **list)
{
	char *firstcommand;
	char **splitedcmd;
	char **splitedcmd2;
	while (1)
	{
		input = readline("cuteshell$> ");
		if (input == NULL)
			break ; // ctrl + D
		if (input[0] != '\0') // working history
			add_history(input);
		command = tokenizer(input);
		if (!command)
			continue;
		if (syntaxerror(command) == 1) 
			continue;
		check_and_expand(final_list,(*command));
		// findredirection((*command));
		firstcommand = join_commands((*command));
		splitedcmd = ft_split(firstcommand, '|');
		set_nonvalidcommand(splitedcmd);
		free(firstcommand);
		int i = 0;
		while (splitedcmd[i])
		{
			splitedcmd2 = ft_split(splitedcmd[i], ' ');
			addback_shellnode(list, create_shellnode(splitedcmd2));
			i++;
		}
		set_backnonvalidcommand(*list);
		findredirection(final_list,*list);
		t_shellcmd *tmp_list = *list;
		while(tmp_list)
   		{
			i = 0;
			while (tmp_list->command[i])
			{
				printf("here-->>|%s|\t", tmp_list->command[i]);
				i++;
			}
			puts(" ");
			tmp_list = tmp_list->next;
   		}
		*list = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	status_exit = 0;
	t_env *env_list;
	t_cmd *command;
	t_shellcmd *finallist;
	
	(void)ac;
	(void)av;
	finallist = NULL;
	command = NULL;
	env_list = NULL;
	input = NULL;
	creat_env_struct(env, &env_list);
	ft_readline(input, &command, env_list, &finallist);
	return (0);
}
