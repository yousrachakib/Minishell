/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-sal <mben-sal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:18:46 by mben-sal          #+#    #+#             */
/*   Updated: 2023/07/23 11:49:15 by mben-sal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_unset(char **cmd, t_env *env)
{
	t_env *current = env;
	while (current)
	{
		if(cmd && ft_strncmp(cmd[2] , env->key, ft_strlen(cmd[2])) == 0)
		{
			free(env->key);
			free(env->value);
			if(current->previous != NULL)
				current->previous->next = current->next;
			else
				env = current->next;
			if(current->next != NULL)
				current->next->previous = current->previous;
			free(current);
			return;
		}
		else
			current = current->next;
	}
}
// void	ft_unset(t_var *var)
// {
// 	t_env	*current;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	while (var->prs->args[i])
// 	{
// 		tmp = var->prs->args[i];
// 		current = var->head_env;
// 		while (current && ft_strncmp(current->key, tmp, ft_strlen(tmp)))
// 			current = current->next;
// 		if (current)
// 		{
// 			free(current->key);
// 			free(current->value);
// 			current->key = NULL;
// 			current->value = NULL;
// 		}
// 		i++;
// 	}
// 	var->status = 0;
// }
// void ft_unset(char **cmd, t_env **env) {
//     t_env *current = *env;

//     while (current) {
//         if (cmd && ft_strncmp(cmd[2], current->key, ft_strlen(cmd[2])) == 0) 
// 		{
//             free(current->key);
//             free(current->value);

//             // Mettre à jour les liens pour supprimer le nœud de la liste
//             if (current->previous != NULL) 
//                 current->previous->next = current->next;
//              else 
//                 // Si le nœud à supprimer est la tête, mettre à jour la tête de la liste
//                 *env = current->next;
//             if (current->next != NULL) {
//                 current->next->previous = current->previous;
//             }

//             free(current); // Libérer la mémoire occupée par le nœud courant
//             return; // Sortir de la fonction après la suppression du nœud
//         } else {
//             current = current->next; // Avancer le pointeur current dans la liste
//         }
//     }

//     // Si la clé n'a pas été trouvée dans la liste
//     printf("La variable d'environnement avec la clé %s n'existe pas.\n", cmd[2]);
// }
