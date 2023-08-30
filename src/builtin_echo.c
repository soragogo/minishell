#include "../includes/minishell.h"

//nオプションは改行しない

static	int		nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void ft_putstr(char *ch, int fd){
	if (!ch)
		return ;
	write(fd, ch, strlen(ch));
}

int				ft_echo(char **args)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		if (args[i] && strncmp(args[i], "-n", 2) == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr(args[i], 1);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}


// #include <stdio.h>
// #include <stdbool.h>
// #include <string.h>

// // テスト用の関数
// void test_builtin_echo(char **argv) {
// 	setbuf(stdout, NULL);
//     printf("Input: ");
// 	fflush(stdout);
//     for (int i = 0; argv[i] != NULL; i++) {
//         printf("%s ", argv[i]);
// 		fflush(stdout);
//     }
//     printf("\nOutput: ");
// 	fflush(stdout);
//     ft_echo(argv);
//     printf("\n\n");
// 	fflush(stdout);
// }

// int main() {
//     // テストケースを用意して実行
//     char *test1[] = {"echo", "Hello,", "world!", NULL};
//     test_builtin_echo(test1);

//     char *test2[] = {"echo", "-n", "No", "newline", "here.", NULL};
//     test_builtin_echo(test2);

//     char *test3[] = {"echo", NULL};
//     test_builtin_echo(test3);

//     return 0;
// }
