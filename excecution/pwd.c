#include "../minishell.h"

void    pwd(t_env *env, char *cmd)
{
    (void)env;
    (void)cmd;
    char *str;

    str = NULL;

    str = getcwd(str, 0);
    printf("%s\n", str);
}