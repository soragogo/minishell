#include "../includes/minishell.h"

char *get_env_name(char *ret, char *env);
char *get_env_value(char *ret, char *env);
void	envmap_init(t_env **map);
int	set_env(t_env **env_head, char *name, char *value);
t_env *item_new(t_env *new_env, char *name, char *value);
void add_new(t_env **map, t_env *new_env);
void env_unset(t_env **env_head, char *delete_env_key);
char *map_get(t_env **env_head, char *name);

// 新しいマップデータ構造を作成
t_env	*map_new(void)
{
	t_env	*map;

	map = calloc(1, sizeof(*map));
	if (map == NULL)
		printf("calloc error");//error
	return (map);
}

//環境変数から変数名取り出す char型じゃなくてよくね？
char *get_env_name(char *ret, char *env)
{
	size_t i;
	size_t j;
	// char *ret;

	i = 0;
	j = 0;
	while(env[i] != '=' && env[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		ret[j] = env[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

//環境変数から値取り出す
char *get_env_value(char *ret, char *env)//""で囲まれてた時とかの処理
{
	size_t i;
	size_t j;
	// char *ret;

	i = 0;
	j = 0;
	while(env[i] != '=' && env[i] != '\0')
		i++;
	ret = malloc(sizeof(char) * strlen(&env[i + 1]) + 1);//strlen書き換え
	while(env[i + j + 1] != '\0')
	{
		ret[j] = env[i + j + 1];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}


//環境変数をマップデータ構造に初期化
void	envmap_init(t_env **map)
{
	extern char **environ;
    char **env = environ;
	char *name;
	char *value;

    while(*env) {
        name = get_env_name(name, *env);
		value = get_env_value(value, *env);
        if(set_env(map, name, value) == -1)
			printf("error");
		// printf("name: %s\nvalue: %s\n",name ,value);
        env++;
    }
}

//マップデータ構造に環境変数を追加
int	set_env(t_env **env_head, char *name, char *value)//値がNULLの場合？
{
	t_env *env;
	t_env *new;

	new = NULL;
	env = *env_head;
	if (name == NULL)// || !is_identifier(name)) //環境変数に設定できない文字ってどれ？
		return (-1);
	while (env && env->name)
	{
		if(strcmp(name, env->name) == 0)
		{
			env_unset(env_head, env->name);
			break ;
		}
		env++;
	}
	// if (env)//すでにあったら一回消す
	// 	env_unset(env_head, env->name);
	new = item_new(new, name, value);
	add_new(env_head, new);
	return (0);
}

//新しいt_envを作成
t_env *item_new(t_env *new_env, char *name, char *value)
{
	new_env = calloc(1, sizeof(*new_env));
	if (!new_env)
		return (NULL);
	new_env->name = name;
	new_env->value = value;
	new_env->next = NULL;

	return (new_env);
}

size_t count_env(t_env *env)
{
	size_t i;

	i = 0;
	while (env && env->name)
	{
		i++;
		env++;
	}
	return (i);
}

//後ろに新しいの追加
void add_new(t_env **map, t_env *new_env)
{
	t_env *env;
	// t_env *prev;
	size_t i;

	env = *map;
	i = count_env(env);
	if (i == 0)
	{
		*map = new_env;
		return ;
	}
	else{
		while ((env)->next)
		{
			// prev = env;
			env = (env)->next;
		}
		// prev->next = *map;
		(env)->next = new_env;
	}
	// while (i >= 1)
	// {
	// 	env++;
	// 	i--;
	// }
	env->next = new_env;
}

//関数は、マップデータ構造からキーで指定された値を削除します。キーが見つからない場合、0が返されます。
void env_unset(t_env **env_head, char *delete_env_key)
{
	t_env *env;
	t_env *prev;

	env = *env_head;
	prev = env;
	if (!delete_env_key)
		return ;
	while (env && env->name)
	{
		if(strcmp(delete_env_key, env->name) == 0)
			break ;
		prev = env;
		env = env->next;
	}
	if (env)
	{
		prev->next = env->next;
		free(env);
	}
}

//関数は、マップデータ構造からキーで指定された値を取得します。キーが見つからない場合、NULLが返されます。
char *map_get(t_env **env_head, char *name)
{
	t_env *env;

	env = *env_head;
	while (env && env->name)
	{
		if(strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


// #include <stdio.h>
// // テスト用の main 関数
// int main() {
//     t_env *map = map_new();
//     envmap_init(&map);
	
// 	printf("1\n");
//     // マップに環境変数を追加するテスト
//     set_env(&map, "TEST_ENV", "Hello, World!");
// 	printf("2\n");
//     set_env(&map, "ANOTHER_ENV", "12345");
// 	printf("3\n");


//     // マップから環境変数の値を取得するテスト
//     printf("TEST_ENV: %s\n", map_get(&map, "TEST_ENV"));
// 	printf("4\n");
//     printf("ANOTHER_ENV: %s\n", map_get(&map, "ANOTHER_ENV"));
// 	printf("5\n");

//     // マップから環境変数を削除するテスト
//     env_unset(&map, "ANOTHER_ENV");
// 	printf("6\n");
	
//     printf("ANOTHER_ENV after unset: %s\n", map_get(&map, "ANOTHER_ENV"));
// 	printf("7\n");

// 	while (map)
// 	{
// 		printf("name: %s\nvalue: %s\n", map->name, map->value);
// 		map = map->next;
// 	}

//     // メモリの解放
//     // ここで実際のコードでは map やその中身の要素を適切に解放する必要があります

//     return 0;
// }
