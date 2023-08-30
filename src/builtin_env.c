#include "../includes/minishell.h"

void ft_env(t_env **env_head, char *arg)
{
	t_env *tmp;

	tmp = *env_head;
	(void)arg;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

// int main(){
// 	char *arg = "env TEST_VARIABLE=hello";
// 	t_env *map = map_new();
//     envmap_init(&map);
// 	ft_env(&map, arg);
// 	return 0;
// }