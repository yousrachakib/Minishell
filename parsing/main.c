/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/21 21:51:01 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(char *input, t_cmd	**command, t_env *final_list)
{
	char *firstcommand;
	char **splitedcmd;
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
		int i = 0;
		while (splitedcmd[i])
		{
			printf("====>> %s\n", splitedcmd[i]);
			protect_inquote(splitedcmd[i]);
			i++;
		}
		// command = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int i = 0;
	status_exit = 0;
	t_env *env_list;
	t_cmd *command;
	
	

	command = NULL;
	env_list = NULL;
	creat_env_struct(env, &env_list);
	ft_readline(input, &command, env_list);
	// while(final_list)
    // {
    //     printf("-->>%s\n", final_list->key);
    //     printf("*****>>%s\n", final_list->value);
    //     final_list = final_list->next;
    // }
	return (0);
}
