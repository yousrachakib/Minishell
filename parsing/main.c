/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/05 16:55:32 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_readline(char *input)
{
	int		i;
	t_cmd	**command;

	command = NULL;
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
		while ((*command))
		{
			printf("****>> %s\n",(*command)->input);
			(*command) = (*command)->next;
		}
		command = NULL;
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	int i = 0;
	t_env *command;
	// command = NULL;
	
	command = malloc(sizeof(t_env));
	init_env(command);
	creat_env_struct(env, &command);
	ft_readline(input);
	return (0);
}
