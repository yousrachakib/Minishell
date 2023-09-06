/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anothernormfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochakib <yochakib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:27:24 by yochakib          #+#    #+#             */
/*   Updated: 2023/09/01 19:49:02 by yochakib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_step(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, controlc);
}

void	ctrl_d(char *input)
{
	if (input == NULL)
		exit (g_j.status_exit);
}

int	emptyline_step(char *input)
{
	if (verify_emptystring(input) == 1)
	{
		free(input);
		return (1);
	}
	return (0);
}

int	syntaxerror_step(t_cmd **command, char *input)
{
	if (syntaxerror(command) == 1)
	{
		free_list(command);
		free(input);
		return (1);
	}
	return (0);
}

int	redirection_step(t_env *env, t_shellcmd **list, t_expand *var, char *input)
{
	if (findredirection(env,*list, var) == 1)
	{
		free_finallist(list);
		free_filelist();
		free(input);
		g_j.signal = 0;
		return (1);
	}
	return (0);
}
