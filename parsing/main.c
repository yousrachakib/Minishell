/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/07/05 17:47:09 by yochakib         ###   ########.fr       */
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
	t_env *final_list;

	final_list = NULL;
	creat_env_struct(env, &final_list);
	while(final_list)
    {
        printf("-->>%s\n", final_list->key);
        printf("*****>>%s\n", final_list->value);
        final_list = final_list->next;
    }
	ft_readline(input);
	return (0);
}
