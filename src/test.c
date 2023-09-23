// #include "./../includes/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*joined;
// 	int		i;
// 	int		strslen;

// 	i = 0;
// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	strslen = strlen(s1) + strlen(s2);
// 	joined = (char *)malloc(sizeof(char) * (strslen + 1));
// 	if (joined == NULL)
// 		return (NULL);
// 	while (*s1)
// 		joined[i++] = *s1++;
// 	while (*s2)
// 		joined[i++] = *s2++;
// 	joined[i] = 0;
// 	return (joined);
// }


// void env_join(char *name, char *value, char **environ)
// {
// 	*environ = ft_strjoin(name, "=");
// 	*environ = ft_strjoin(*environ, value);
// }

// char **create_environ(t_env **env_head)
// {
// 	t_env *tmp;
// 	char **environ;
//     // char **ret;
//     int i;

//     // ret = environ;
//     i = 0;
// 	tmp = *env_head;
// 	while (tmp)
// 	{
// 		// printf("%s=%s\n", tmp->name, tmp->value);
// 		env_join(tmp->name, tmp->value, &environ[i]);
// 		i++;
// 		tmp = tmp->next;
// 	}
//     environ[i] = NULL;
// 	return (environ);
// }

// int main() {
//     // 仮想的な環境変数リストを作成します
//     t_env *env1 = (t_env *)malloc(sizeof(t_env));
//     env1->name = "PATH";
//     env1->value = "/usr/bin:/bin";
//     env1->next = NULL;

//     t_env *env2 = (t_env *)malloc(sizeof(t_env));
//     env2->name = "HOME";
//     env2->value = "/user/home";
//     env2->next = NULL;

//     // 環境変数リストを連結します
//     env1->next = env2;

//     // create_environ 関数を呼び出して environ 形式の文字列配列を作成します
//     char **environ = create_environ(&env1);

//     // environ の内容を表示します
//     for (int i = 0; environ[i] != NULL; i++) {
//         printf("%s\n", environ[i]);
//     }

//     // メモリの解放を行います
//     // この部分のメモリ管理は実際のプログラムに合わせて適切に行ってください
//     for (int i = 0; environ[i] != NULL; i++) {
//         free(environ[i]);
//     }
//     // free(environ);
    
//     // // ダミー環境変数リストのメモリ解放
//     // free(env1);
//     // free(env2);

//     return 0;
// }
