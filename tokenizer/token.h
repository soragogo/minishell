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
	NON_EXPANDABLE,//''
	EXPANDABLE_QUOTED,//""
	PIPE,//|
	EXPANDABLE,//command, option
	REDIRECTIONS,//<>
} TYPE;

typedef struct s_list_token
{
	char *arg;
	TYPE type;
	int is_freed;
} t_token;

t_token *ft_tokenizer(char *command);

#endif
