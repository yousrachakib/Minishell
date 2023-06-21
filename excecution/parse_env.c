#include "../minishell.h"

t_env	*ft_lstlast(t_env *lst)
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

t_env *create_nodee(char *key, char *val)
{
    t_env *tmp;

    tmp = malloc(sizeof (t_env) * 1);
    tmp->key = key;
    tmp->value = val;
    tmp->next = NULL;
    return (tmp);
}


void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			tmp = ft_lstlast(*(lst));
			tmp->next = new;
		}
	}
}

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}


int parse_env(char **str, t_data **data)
{
    int i;
    char **tmp;

    i = 0;
    while (str[i])
    {
		tmp = split_nodes(str[i],'=');
        if (i == 0)
            (*data)->env = create_nodee(tmp[0],tmp[1]);
		else
        	ft_lstadd_back(&(*data)->env,create_nodee(tmp[0], tmp[1]));
        i++;
    }
	i = 0;
	 while (str[i])
    {
		tmp = split_nodes(str[i],'=');
        if (i == 0)
            (*data)->export = create_nodee_export(tmp[0],tmp[1]);
		else
        	ft_lstadd_backexport(&(*data)->export,create_nodee_export(tmp[0], tmp[1]));
        i++;
    }

    return (1);
}