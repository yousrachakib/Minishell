#include "../minishell.h"

// void	store_cmd(t_data *data, char *input)
// {
// 	int	i;

// 	i = 0;
// 	data->cmd->cmd = malloc(sizeof(char *) * 5);
// 	data->cmd->cmd = ft_split(input, " ");
// 	i = 0;
// 	// while (data->cmd->cmd[i])
// 	// {
// 	// 	printf("%s\n", data->cmd->cmd[i]);
// 	// 	i++;
// 	// }
// }

void	sort_list(t_export **head)
{
	int		i;
	t_export	*current;
	t_export	*previous;
	t_export	*temp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	i = 0;
	while (i == 0)
	{
		i = 1;
		current = *head;
		previous = NULL;
		while (current->next != NULL)
		{
			if (strcmp(current->key, current->next->key) > 0)
			{
				i = 0;
				temp = current->next;
				current->next = temp->next;
				temp->next = current;
				if (previous != NULL)
					previous->next = temp;
				else
					*head = temp;
				current = temp;
			}
			previous = current;
			current = current->next;
		}
	}
}

void	excecution(t_env *env, t_data **data, char **envp)
{

	if (strcmp((*data)->line[0], "pwd") == 0)
	{
		pwd(env, (*data)->line[0]);
	}
	else if (strcmp((*data)->line[0], "env") == 0)
	{
		while (env != NULL)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else if (strcmp((*data)->line[0], "exit") == 0)
	{
		exit(0);
	}
	else if (strcmp((*data)->line[0], "cd") == 0)
	{
		cd(env, (*data)->line);
	}
	else if (strcmp((*data)->line[0], "export") == 0)
	{
		export((*data)->line, (*data)->export);
	}
	else if (strcmp((*data)->line[0], "echo") == 0)
	{
		echo((*data) , (*data)->line);
	}
	else
		nrml_commands(env, data, envp);
}