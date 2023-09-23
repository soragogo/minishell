#include <libc.h>
#include "../includes/minishell.h"

char *fetch_path(char *file)
{
	char path[PATH_MAX];
	char *pathlist = getenv("PATH");
	//printf("pathlist: [%s]\n", pathlist);

	char *start = pathlist;
	char *end = NULL;
	// char *tmp;
	char *result;
	int flag = 0;
	while (flag == 0)
	{
		bzero(path, PATH_MAX);
		if (end != NULL && *(end + 1)!='\0')
			start = end + 1;
		end = ft_strchr(start, ':');
		if (end)
		{
			strlcpy(path, start, end - start + 1);
		}
		else
		{
			flag = 1;
			strcpy(path, start);
		}
		strlcat(path, "/", PATH_MAX);
		strlcat(path, file, PATH_MAX);

	if (access(path, F_OK) == 0)
	{
//		printf("path: [%s]\n",path);
		result = ft_strdup(path);
		return (result);
	}
	}
	return (NULL);
}

t_token *search_path(t_token *tokens)
{
	t_token *tmp_tokens = tokens;
	char *tmp;
	for (int i = 0; tmp_tokens[i].arg != NULL; i++)
	{
		tmp = fetch_path(tmp_tokens[i].arg);
		if (tmp != NULL)
		{
			// free(tmp_tokens[i].arg);
			tmp_tokens[i].arg = tmp;
		}
	}
	return (tmp_tokens);
}

// #include "../includes/minishell.h"
// #include <unistd.h>
// int main()
// {
// 	char *command_buf;
// 	while (1)
// 	{
// 		command_buf = readline("exec_path> ");
// 		search_path(command_buf);
// 		printf("%s\n", command_buf);
// 		if (command_buf != NULL)
// 			exec(command_buf);
// 		free(command_buf);
// 	}	return (0);
// }
