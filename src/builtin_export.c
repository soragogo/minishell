#include "../includes/minishell.h"

void ft_export(t_env **map, char *arg)
{
	char *name;
	char *value;

	name = get_env_name(name, arg);
	value = get_env_value(value, arg);
	if(set_env(map, name, value) == -1)
		printf("error");
	// set_env(&map, "TEST_VARIABLE", "hello");
}

// int main(){
// 	t_env *map = map_new();
//     envmap_init(&map);
// 	char *arg = "TEST_VARIABLE=hello";
// 	ft_env(&map, arg);
// 	printf("----------------------------------------\n");
// 	ft_export(&map, arg);
// 	ft_env(&map, arg);
// 	return 0;
// }