#include <libc.h>
char *search_path(char *file)
{
	char path[PATH_MAX];
	char *pathlist = getenv("PATH");
	printf("pathlist: [%s]\n", pathlist);
	
	char *start = pathlist;
	char *end = NULL;
	char *tmp;
	char *result;
	for (int i = 0; i < 15; i++)
	{
		bzero(path, PATH_MAX);
		if (end != NULL && *(end + 1)!='\0')
			start = end + 1;
		end = strchr(start, ':');
		if (end)
		{
			strlcpy(path, start, end - start + 1);
		}
		else
		{
			strcpy(path, start);
		}
		strlcat(path, "/", PATH_MAX);
		strlcat(path, file, PATH_MAX);
	
	printf("path: [%s]\n",path);
	if (access(path, F_OK) == 0)
	{
		printf("fileexist\n");
		result = strdup(path);
		return (result);
	}
	else
		printf("KO\n");
	}
	return (pathlist);
}
/*
int main()
{
	char *commands[] = {"ls", "pwd", NULL};
	int i = 0;
	while (commands[i])
	{
		puts("----------------------------");
		search_path(commands[i]);
		i++;
	}
}*/
