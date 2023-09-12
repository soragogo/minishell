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
<<<<<<< HEAD
	NON_EXPANDABLE,//''
	EXPANDABLE_QUOTED,//""
	PIPE,//|
	EXPANDABLE,//command, option
	REDIRECTIONS,//<>
=======
	UNCATEGORIZED,
	PIPE,		   // | (パイプ)
	REDIRECT_OUT,  // > (リダイレクト出力)
	REDIRECT_IN,   // < (リダイレクト入力)
	APPEND_OUT,	   // >> (出力の追加)
	HERE_DOCUMENT, // << (ヒアドキュメント)
	COMMAND,
	COMMAND_OPTION,
	FILE_NAME
>>>>>>> ffd562c95b262524d0e74e84217e6a8f6d89be3e
} TYPE;

typedef struct s_list_token
{
	char *arg;
	TYPE type;
	int is_freed;
} t_token;

t_token *ft_tokenizer(char *command);

#endif
