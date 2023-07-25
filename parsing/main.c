/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/25 17:12:17 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd **list)
{
	char *firstcommand;
	char **splitedcmd;
	char **splitedcmd2;
	(void )list;
	
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
		free(firstcommand);
		int i = 0;
		while (splitedcmd[i])
		{
			splitedcmd2 = ft_split(splitedcmd[i], ' ');
			addback_shellnode(list, create_shellnode(splitedcmd2));
			i++;
		}
		t_shellcmd *tmp_list = *list;
		while(tmp_list)
   		{
			i = 0;
			while (tmp_list->command[i])
			{
				printf("tmp-->>%s\n", tmp_list->command[i]);
				i++;
			}
			tmp_list = tmp_list->next;
   		}
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
	// finallist = malloc(sizeof(t_shellcmd));
	finallist = NULL;
	command = NULL;
	input = NULL;
	creat_env_struct(env, &env_list);
	ft_execution(av, env_list);
	ft_readline(input, &command, env_list, &finallist);
	// while(finallist)
    // {
	// 	while (finallist->command[i])
    //     {
	// 		printf("-->>%s\n", finallist->command[i]);
	// 		i++;
	// 	}
    //     finallist = finallist->next;
    // }
	return (0);
}
