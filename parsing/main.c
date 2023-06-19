/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:10:31 by yochakib          #+#    #+#             */
/*   Updated: 2023/06/19 18:09:06 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	init_struct(t_cmd	*command)
{
	command->input = NULL;
	command->fd_input = 0;
	command->fd_output = 0;
	command->next = NULL;
}
void	syntaxerror(char *input)
{
	if (check_quotes(input))
	{
		printf("syntaxError : verify quotations\n");
		return ;
	}
	if (pipe_errors(input))
	{
		printf("syntax error\n");
		return ;
	}
	if (special_char_only(input))
	{
		printf("syntax error\n");
		return ;
	}
}

void ft_readline(char *input)
{
	int		i;
	char	**newinput;
	t_cmd	*command;

	i = 0;
	while (1)
	{
		input = readline("cuteshell$> ");
		if (input == NULL)
			break; //handling EOF control+D
		if (input[0] != '\0')
			add_history(input);
		protect_inquote(input);
		init_struct(command);
		newinput = ft_split(input, '|');
		while (newinput[i])
		{
			addback_node(&command, create_node(newinput[i]));
			printf("---->>%s\n", create_node(newinput[i])->input);
			i++;
		}
		// syntaxerror(input);
		free(input);
	}
}

int main(int ac, char **av)
{
	char *input;
	ft_readline(input);
}