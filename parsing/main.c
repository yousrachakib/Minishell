/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/23 17:35:19 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	syntaxerror(char *input)
// {
// 	if (check_quotes(input))
// 	{
// 		printf("syntaxError : verify quotations\n");
// 		return ;
// 	}
// 	if (pipe_errors(input))
// 	{
// 		printf("syntax error\n");
// 		return ;
// 	}
// 	if (special_char_only(input))
// 	{
// 		printf("syntax error\n");
// 		return ;
// 	}
// }

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
		// if (check_quotes(input))
		// {
		// 	printf("syntaxError : verify quotations\n");
		// 	return ;
		// }
		// protect_inquote(input);
		command = tokenizer(input);
		if (!command)
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
