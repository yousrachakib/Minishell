/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/19 14:03:37 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(char *input, t_cmd	**command, t_env *final_list)
{
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
		while ((*command))
		{
			printf("****>> %s\n",(*command)->input);
			(*command) = (*command)->next;
			// ft_echo()
		}
		command = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int i = 0;
	status_exit = 0;
	t_env *final_list;
	t_cmd *command;

	command = NULL;
	final_list = NULL;
	creat_env_struct(env, &final_list);
	// while(final_list)
    // {
    //     printf("%s=%s\n", final_list->key, final_list->value);
    //     // printf("||*****>>%s\n", );
    //     final_list = final_list->next;
    // } 
	ft_readline(input, &command, final_list);
	return (0);
}
