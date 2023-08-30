#include "../includes/minishell.h"

void ft_export(t_env **map, char **arg)
{
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	name = get_env_name(name, arg[1]);
	value = get_env_value(value, arg[1]);
	if(set_env(map, name, value) == -1)
		printf("error");
	// set_env(&map, "TEST_VARIABLE", "hello");
}


// void test_ft_export(t_env **map, char **arg) {
//     printf("Setting environment variable: %s\n", *arg);
//     ft_export(map, arg);
//     printf("Environment variable set.\n\n");
// }

// int main() {
//     // テストケースを用意して実行
//     t_env *map = map_new();
//     envmap_init(&map);  // mapの初期化は実際の状況に合わせて修正
    

//     // char *test1 = "MY_VARIABLE=value123";
// 	char *test1[] = {"export", "MY_VARIABLE=value123"};
// 	ft_env(&map, *test1);
//     test_ft_export(&map, test1);

//     char *test2[] = {"export", "ANOTHER_VARIABLE=hello_world"};
//     test_ft_export(&map, test2);
	
// 	printf("----------------------------------------\n");
// 	ft_env(&map, *test1);

//     return 0;
// }