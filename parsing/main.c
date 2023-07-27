/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/27 21:22:38 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(char *input, t_cmd	**command, t_env *final_list, t_shellcmd *list)
{
	list = NULL;
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
		t_cmd *tmp;
		tmp = (*command);
		list = findredirection((*command));
		if (list == NULL)
			continue;
		int i = 0;
		t_shellcmd *tmp_list = list;
		while(tmp_list)
   		{
			i = 0;
			while (tmp_list->command[i])
			{
				printf("****>> %s\n", tmp_list->command[i]);
				printf("****>> %d\n", tmp_list->fd_out);
				printf("****>> %d\n", tmp_list->fd_in);
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
	finallist = NULL;
	command = NULL;
	env_list = NULL;
	input = NULL;
	creat_env_struct(env, &env_list);
	ft_readline(input, &command, env_list, finallist);
	return (0);
}
