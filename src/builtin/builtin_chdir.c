#include "../includes/minishell.h"
// char *home;
// char *dir_path;

// int update_pwd(char *new_pwd)
// {
// 	set_env("PWD", new_pwd, 1);
// }

int ft_chdir(char **command_buf, t_env **env)
{
	char *home;
	char *dir_path;
	// char *old_pwd;
	home = getenv("HOME");
	if (!home){
		printf("HOME not set");
		return (1);
	}
	dir_path = getenv("PWD");
	if (!dir_path){
		printf("PWD not set");
		return (1);
	}
	set_env(env, "OLDPWD", dir_path);
	if (command_buf[1] == NULL)//引数がない場合
		strlcpy(dir_path, home, PATH_MAX);//後で書き換え
	else if (command_buf[1][0] == '~')//引数が~の場合
	{
		strlcpy(dir_path, home, PATH_MAX);//
		strlcat(dir_path, command_buf[1] + 1, PATH_MAX);//
	}
	else if (command_buf[1][0] == '-')//引数が-の場合
	{
		dir_path = getenv("OLDPWD");
		if (!dir_path){
			printf("OLDPWD not set");
			return (1);
		}
		printf("%s\n", dir_path);
	}
	else//ディレクトリ直書きの場合
	{
		if (command_buf[1][0] == '/')
			strlcpy(dir_path, command_buf[1], PATH_MAX);//
		else
		{
			strlcat(dir_path, "/", PATH_MAX);//
			strlcat(dir_path, command_buf[1], PATH_MAX);//
		}
	}
	if (chdir(dir_path) != 0)
	{
		printf("cd: no such file or directory: %s\n", dir_path);
		return (1);
	}
	// update_pwd(dir_path);
	set_env(env, "PWD", dir_path);
	return (0);
}


// テスト用の関数
void test_ft_chdir(char **command_buf, t_env **env) {
    printf("Command: ");
    for (int i = 0; command_buf[i] != NULL; i++) {
        printf("%s ", command_buf[i]);
    }
    printf("\n");
    
    int result = ft_chdir(command_buf, env);
    
    if (result == 0) {
        printf("Directory changed successfully.\n");
    } else {
        printf("Directory change failed.\n");
    }
	printf("OLDPWD: %s\n", getenv("OLDPWD"));
	printf("PWD: %s\n", getenv("PWD"));
    printf("\n");
}

int main() {
    // テストケースを用意して実行
    t_env *env = map_new();
    envmap_init(&env);
    
    char *test1[] = {"cd", NULL};
    test_ft_chdir(test1, &env);

    char *test2[] = {"cd", "~/Documents", NULL};
    test_ft_chdir(test2, &env);

    char *test3[] = {"cd", "-", NULL};
    test_ft_chdir(test3, &env);

    char *test4[] = {"cd", "/tmp", NULL};
    test_ft_chdir(test4, &env);

    return 0;
}
