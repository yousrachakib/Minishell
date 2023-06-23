/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/23 20:26:29 by yochakib         ###   ########.fr       */
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
			break ;
		if (input[0] != '\0')
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

int	main(int ac, char **av)
{
	char	*input;
	ft_readline(input);
	return (0);
}
