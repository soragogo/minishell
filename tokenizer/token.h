#ifndef TOKEN_H
#define TOKEN_H

#include <libc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef enum
{
	// UNCATEGORIZED,
	// PIPE,		   // | (パイプ)
	REDIRECT_OUT,	// > (リダイレクト出力)
	REDIRECT_IN,	// < (リダイレクト入力)
	APPEND_OUT,		// >> (出力の追加)
	HERE_DOCUMENT	// << (ヒアドキュメント)
	// COMMAND,
	// COMMAND_OPTION,
	// FILE_NAME
} TYPE;

typedef struct s_redirect
{
	TYPE redir_type;
	int newfd;
	int stashfd;
	int oldfd;
	const char *filename;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}	t_redirect;

typedef struct s_list_token
{
	char *arg;
	TYPE type;
	int is_freed;
	t_redirect *node;
	struct s_list_token *next_token;
} t_token;

t_token *ft_tokenizer(char *command);

#endif
