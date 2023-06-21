#include "../minishell.h"

// static void	printLinkedList_export(t_export *head)
// {
// 	t_export	*currentNode;

// 	currentNode = head;
// 	while (currentNode != NULL)
// 	{
// 		printf("declare -x %s=\"%s\"\n", currentNode->key, currentNode->value);
// 		currentNode = currentNode->next;
// 	}
// }
t_export	*ft_lstlast_export(t_export *lst)
{
	while (lst)
	{
		if (!lst->next)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}
t_export *create_nodee_export(char *key, char *val)
{
    t_export *tmp;

    tmp = malloc(sizeof (t_export) * 1);
    tmp->key = key;
	tmp->value = val;
    tmp->next = NULL;
    return (tmp);
}

void	ft_lstadd_backexport(t_export **lst, t_export *new)
{
	t_export	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast_export(*(lst));
			tmp->next = new;
		}
	}
}

void	check_and_add(t_export *env, char **line)
{
	int		i;
	(void)env;
	char	**str;
	char	*key;
	char	*value;

	i = 0;
	str = split_nodes(line[1], '=');
	key = strdup("");
	key = str[0];
	value = strdup("");
	value = str[1];
	while (line[i])
		i++;
	if (i != 2)
		printf("not a valid identifier\n");
	ft_lstadd_backexport(&env, create_nodee_export(key, value));
}
// int search_space(char *str)
// {
// 	int i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=' && str[i + 1] == ' ')
// 			return (1);
		
// 	}
// }
void	export(char **line, t_export *export)
{
	int i = 0;
	//printf("%s // %s", export->key, export->value);
	while (line[i])
		i++;
	if (line[1] != NULL)
		check_and_add(export, line);
	else
	{
		sort_list(&export);
		while (export != NULL) 
		{
			printf("declare -x %s=\"%s\"\n", export->key, export->value);
		 	export = export->next;
		}
	}
}