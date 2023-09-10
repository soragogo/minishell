#include "./../includes/minishell.h"

void ft_putstr(char *ch, int fd)
{
	if (!ch)
		return;
	write(fd, ch, strlen(ch));
}

int ft_echo(t_token *tokens, int status)
{
	int i;
	int n_option;

	i = 1;
	n_option = 0;
	if (tokens[i].arg && strncmp(tokens[i].arg, "-n", 2) == 0 && strlen(tokens[i].arg) == 2)
	{
		n_option = 1;
		i++;
	}
	while (tokens[i].arg)
	{
		if (tokens[i].arg && strncmp(tokens[i].arg, "$?", 2) == 0)
		{
			ft_putnbr_fd(status, 1);
			if (tokens[i].arg[2])
				ft_putstr(&tokens[i].arg[2], 1);
		}
		else
			ft_putstr(tokens[i].arg, 1);
		i++;
		if (tokens[i].arg)
			write(1, " ", 1);
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
//     ft_echo(argv, 1);
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

// 	char *test4[] = {"echo", "$?", NULL};
// 	test_builtin_echo(test4);

//     return 0;
// }
