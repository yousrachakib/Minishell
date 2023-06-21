#include "../minishell.h"




int remove_key(t_env **head, const char *key) {
    t_env *current = *head;
    t_env *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (previous == NULL) 
            {
                *head = current->next;
            } 
            else {
                previous->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return (0);
        }
        previous = current;
        current = current->next;
    }
    return (1);
}
// static char* search_key(t_env* head, const char* key)
// {
//     t_env* current = head;
//     while (current != NULL)
//     {
//         if (strcmp(current->key, key) == 0)
//         {
//             return current->key;
//         }
//         current = current->next;
//     }
//     return (NULL);
// } 
// void    unset(char **line, t_env *env)
// {
//     char *s = search_key(env, line[1]);
//     // if (remove_key(&env, s) == 1)
//     // {
//     //     puts("")
//     // }
// }