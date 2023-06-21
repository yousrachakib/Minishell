#include "../minishell.h"


void    nrml_commands(t_env *env, t_data **data, char **envp)
{
	(void)envp;
	char *path = NULL;
	t_env *tmp = env;
	char **tmm = NULL;
	while (tmp != NULL)
	{
		if (strcmp(tmp->key, "PATH") == 0)
		{
			path = strdup(tmp->value);
			break;
		}
		tmp = tmp->next;
	}
	tmm = ft_split(path, ":");

	int i = 0;
	char *s;
	char *tmp1;
	if (access((*data)->line[0], F_OK | X_OK) != 0)
	{
		while (tmm[i])
		{
			tmp1 = ft_strjoin(tmm[i], "/");
			s = ft_strjoin(tmp1,(*data)->line[0]);
			free(tmp1);
			if (access(s, F_OK | X_OK) == 0)
			{
				break ;
			}
			i++;
		}
		if (access(s, F_OK | X_OK) != 0)
			s = strdup((*data)->line[0]);
	}
	else
		s = strdup((*data)->line[0]);
	int var = fork();
	if (var == 0)
	{
		if (execve(s, (*data)->line, envp) == -1)
		{
			write (2, "minishell: ", ft_strlen("minishell: "));
			write (2, s, ft_strlen(s));
			perror(" ");
		}
		// write(1, "\n", 1);
		free(s);
	}
	else
	{
		int status;
		if (waitpid(var, &status, 0) == -1)
			perror("");
	}
}