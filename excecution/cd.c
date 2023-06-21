#include "../minishell.h"

char* search(t_env* head, const char* key)
{
    t_env* current = head;
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void update_value(t_env *head, const char *key, const char *newValue)
{
    t_env *current = head;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = strdup(newValue);
            return; 
        }
        current = current->next;
    }
}


// void printLinkedList(t_env *head)
// {
//     t_env *currentNode = head;

//     while (currentNode != NULL)
//     {
//         printf("%s=%s\n", currentNode->key, currentNode->value);
//         currentNode = currentNode->next;
//     }
// }
void    cd(t_env *env, char **line)
{
    (void)line;
    char *pwd;
    char *path;
    int i;

    i = 0;
    while (line[i])
        i++;
    if (i == 1)
    {
        char *s;

        s = search(env, "HOME");
        chdir (s);
    }
    path = NULL;
    chdir(line[1]);
    pwd = search(env, "PWD");
    update_value(env, "OLDPWD", pwd);
    path = getcwd(path, 0);
    update_value(env, "PWD", path);
}