#include "../includes/minishell.h"

//後で綺麗にします
void ft_unset(t_env **env_head, char *name)
{
	env_unset(env_head, name);
}

// int main (){
// 	t_env *map = map_new();
//     envmap_init(&map);
// 	set_env(&map, "TEST_VARIABLE", "hello");
// 	char *arg = "TEST_VARIABLE";
// 	ft_env(&map, arg);
// 	printf("----------------------------------------\n");
// 	ft_unset(&map, arg);
// 	ft_env(&map, arg);
// 	return 0;
// }